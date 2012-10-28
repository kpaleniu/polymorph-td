/**
 * @file VertexBuffer.cpp
 *
 */

#include "gr/VertexBuffer.hpp"
#include "gr/BufferManager.hpp"
#include "gr/GraphicsException.hpp"

#include "Assert.hpp"
#include "Debug.hpp"

namespace gr {

namespace {
const char* TAG = "VertexBuffer";
}

VertexBuffer::VertexBuffer(BufferManager& manager,
                           VertexFormat format,
                           BufferUsage usage,
                           size_t vertexCount,
                           const real* data)
:	_bufferID(0),
 	_vertexCount(vertexCount),
 	_vertexFormat(format),
 	_manager(manager)
{
#ifdef _DEBUG
	VERBOSE_OUT(TAG, "Size %i", (int) getVertexFormatData(_vertexFormat).size);
	VERBOSE_OUT(TAG, "vert dim %i", (int) getVertexFormatData(_vertexFormat).vertDim);
	VERBOSE_OUT(TAG, "Count %i", vertexCount);
	for (unsigned int i = 0;
		 i < _vertexCount * getVertexFormatData(_vertexFormat).size;
		 ++i)
	{
		VERBOSE_OUT(TAG, "%f ", data[i]);
	}
#endif

	glGenBuffers(1, &_bufferID);

	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);

	// Vertices are saved as [v1, ..., vN, c1, ..., cN, t1, ..., tN, n1, ..., nN]
	//  v - vertex
	//  c - color
	//  t - texture coordinate
	//  n - normal

	glBufferData(GL_ARRAY_BUFFER,
	             _vertexCount * getVertexFormatData(_vertexFormat).size,
	             data,
	             GLenum(usage));

	GLint bufferSize = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	if ( bufferSize != GLint(_vertexCount * getVertexFormatData(_vertexFormat).size) )
	{
		glDeleteBuffers(1, &_bufferID);
		_bufferID = 0;

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		throw GraphicsException("Error while creating buffer");
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer)
:	_bufferID(vertexBuffer._bufferID),
 	_vertexCount(vertexBuffer._vertexCount),
 	_vertexFormat(vertexBuffer._vertexFormat),
 	_manager(vertexBuffer._manager)
{
	vertexBuffer._bufferID = 0;
}

VertexBuffer::~VertexBuffer()
{
	if (_bufferID != 0)
	{
		glDeleteBuffers(1, &_bufferID);
		_bufferID = 0;
	}
}

void VertexBuffer::writeVertices(size_t offset,
                                 size_t count,
                                 const real* verts)
{
	ASSERT(getVertexFormatData(_vertexFormat).vertDim != 0,
	       "Vertices don't store vertices?");

	write(size_t(startOf(VertexFormatFlag::VERT_FLAG)) + offset,
	      count * getVertexFormatData(_vertexFormat).vertDim,
	      verts);
}

void VertexBuffer::writeColors(size_t offset,
                               size_t count,
                               const real* colors)
{
	ASSERT(getVertexFormatData(_vertexFormat).colorDim != 0,
	       "Vertices don't store colors");

	write(size_t(startOf(VertexFormatFlag::COLOR_FLAG)) + offset,
	      count * getVertexFormatData(_vertexFormat).colorDim,
	      colors);
}

void VertexBuffer::writeTextureCoords(size_t offset,
                                      size_t count,
                                      const real* texCoords)
{
	ASSERT(getVertexFormatData(_vertexFormat).textDim != 0,
	       "Vertices don't store texture coordinates");

	write(size_t(startOf(VertexFormatFlag::TEXT_FLAG)) + offset,
	      count * getVertexFormatData(_vertexFormat).textDim,
	      texCoords);
}

void VertexBuffer::writeNormals(size_t offset,
                                size_t count,
                                const real* normals)
{
	ASSERT(getVertexFormatData(_vertexFormat).normalDim != 0,
	       "Vertices don't store normal coordinates");

	write(size_t(startOf(VertexFormatFlag::NORMAL_FLAG)) + offset,
	      count * getVertexFormatData(_vertexFormat).normalDim,
	      normals);
}

void VertexBuffer::draw(Primitive primitive)
{
	const VertexFormatData& formatData = getVertexFormatData(_vertexFormat);
	_manager.setFormat(formatData.fmtFlags);

	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);

	if ( (formatData.fmtFlags & (unsigned char) VertexFormatFlag::VERT_FLAG) != 0)
	{
		glVertexPointer(formatData.vertDim,
		                REAL_TYPE, 0,
		                startOf(VertexFormatFlag::VERT_FLAG));
	}
	if ( (formatData.fmtFlags & (unsigned char) VertexFormatFlag::COLOR_FLAG) != 0)
	{
		glColorPointer(formatData.colorDim,
		               REAL_TYPE, 0,
		               startOf(VertexFormatFlag::COLOR_FLAG));
	}
	if ( (formatData.fmtFlags & (unsigned char) VertexFormatFlag::TEXT_FLAG) != 0)
	{
		glTexCoordPointer(formatData.textDim,
		                  REAL_TYPE, 0,
		                  startOf(VertexFormatFlag::TEXT_FLAG));
	}
	if ( (formatData.fmtFlags & (unsigned char) VertexFormatFlag::NORMAL_FLAG) != 0)
	{
		ASSERT(formatData.normalDim == 3, "Bad normal dimension");
		glNormalPointer(REAL_TYPE, 0,
		                startOf(VertexFormatFlag::NORMAL_FLAG));
	}

	glDrawArrays(GLenum(primitive), 0, _vertexCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/*
void VertexBuffer::draw(Primitive primitive,
                        const IndexBuffer& indices)
{
	ASSERT(_manager.isEnabled(), "Vertex buffers must be enabled for this");

}
*/
void VertexBuffer::write(size_t offset,
                         size_t size,
                         const real* verts)
{
	glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, verts);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const void* VertexBuffer::startOf(VertexFormatFlag type) const
{
	const VertexFormatData& formatData = getVertexFormatData(_vertexFormat);

	switch (type)
	{
		case VertexFormatFlag::VERT_FLAG:
			return 0;

		case VertexFormatFlag::COLOR_FLAG:
			return (void*)(_vertexCount * formatData.vertDim);

		case VertexFormatFlag::TEXT_FLAG:
			return (void*)(_vertexCount * (	formatData.vertDim +
											formatData.colorDim ));

		case VertexFormatFlag::NORMAL_FLAG:
			return (void*)(_vertexCount * (	formatData.vertDim +
											formatData.colorDim +
											formatData.textDim ));
	}

	ASSERT(false, "Parameter isn't of type VertexFormatFlag");

	return (void*) 0;
}

}
