/**
 * @file VertexBuffer.cpp
 *
 */

#include "gr/VertexBuffer.hpp"
#include "gr/GraphicsException.hpp"

#include <Assert.hpp>
#include <Debug.hpp>

namespace gr {

namespace {

const char* TAG = "VertexBuffer";

void enableVertexFormats(const VertexFormatData& formatData)
{
	format_flags enableFmt = formatData.fmtFlags;

	if ( enableFmt & VertexFormatFlag::VERT_FLAG )
		gl::enableClientState(GL_VERTEX_ARRAY);

	if ( enableFmt & VertexFormatFlag::COLOR_FLAG )
		gl::enableClientState(GL_COLOR_ARRAY);

	if ( enableFmt & VertexFormatFlag::TEXT_FLAG )
		gl::enableClientState(GL_TEXTURE_COORD_ARRAY);

	if ( enableFmt & VertexFormatFlag::NORMAL_FLAG )
		gl::enableClientState(GL_NORMAL_ARRAY);
}

void disableVertexFormats(const VertexFormatData& formatData)
{
	format_flags disableFmt = formatData.fmtFlags;

	if ( disableFmt & VertexFormatFlag::VERT_FLAG )
		gl::disableClientState(GL_VERTEX_ARRAY);

	if ( disableFmt & VertexFormatFlag::COLOR_FLAG )
		gl::disableClientState(GL_COLOR_ARRAY);

	if ( disableFmt & VertexFormatFlag::TEXT_FLAG )
		gl::disableClientState(GL_TEXTURE_COORD_ARRAY);

	if ( disableFmt & VertexFormatFlag::NORMAL_FLAG )
		gl::disableClientState(GL_NORMAL_ARRAY);
}

}

VertexBuffer::VertexBuffer(VertexFormat format,
                           BufferUsage usage,
                           size_t vertexCount,
                           const real_t* data)
:	_bufferID(0),
	_vertexCount(vertexCount),
	_usage(usage),
	_vertexFormat(format)
{
#ifdef _DEBUG
	VERBOSE_OUT(TAG,
	            "Size %i", (int) getVertexFormatData(_vertexFormat).size);
	VERBOSE_OUT(TAG,
	            "vert dim %i", (int) getVertexFormatData(_vertexFormat).vertDim);
	VERBOSE_OUT(TAG, "Count %i", vertexCount);
	if (data != nullptr)
	{
		for (unsigned int i = 0;
			 i < _vertexCount * getVertexFormatData(_vertexFormat).size;
			 ++i)
		{
			VERBOSE_OUT(TAG, "%f ", data[i]);
		}
	}
#endif
	if (vertexCount > 0)
	{
		gl::genBuffers(1, &_bufferID);

		gl::bindBuffer(GL_ARRAY_BUFFER, _bufferID);

		// Vertices are saved as [v1, ..., vN, c1, ..., cN, t1, ..., tN, n1, ..., nN]
		//  v - vertex
		//  c - color
		//  t - texture coordinate
		//  n - normal

		gl::bufferData(GL_ARRAY_BUFFER,
		             _vertexCount
		             * getVertexFormatData(_vertexFormat).size
		             * sizeof(real_t),
		             data,
		             usage);

		GLint bufferSize = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER,
		                       GL_BUFFER_SIZE,
		                       &bufferSize);

		DEBUG_OUT(TAG, "Allocated VertexBuffer %i: %i bytes.", _bufferID, bufferSize);

		if (bufferSize != GLint(_vertexCount
								* getVertexFormatData(_vertexFormat).size
								* sizeof(real_t)))
		{
			gl::deleteBuffers(1, &_bufferID);
			_bufferID = 0;

			gl::bindBuffer(GL_ARRAY_BUFFER, 0);

			throw GraphicsException();
		}

		gl::bindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer)
:	_bufferID(vertexBuffer._bufferID),
 	_vertexCount(vertexBuffer._vertexCount),
 	_usage(vertexBuffer._usage),
 	_vertexFormat(vertexBuffer._vertexFormat)
{
	vertexBuffer._bufferID = 0;
	vertexBuffer._vertexCount = 0;
}

VertexBuffer::~VertexBuffer()
{
	if (_bufferID != 0)
	{
		gl::deleteBuffers(1, &_bufferID);
		DEBUG_OUT(TAG, "Deallocated VertexBuffer %i", _bufferID);
		_bufferID = 0;
	}
}

void VertexBuffer::writeVertices(size_t offset,
                                 size_t count,
                                 const real_t* verts)
{
	ASSERT(getVertexFormatData(_vertexFormat).vertDim != 0,
	       "Vertices don't store vertices?");

	write(size_t(startOf(VertexFormatFlag::VERT_FLAG))
	      + offset * getVertexFormatData(_vertexFormat).vertDim * sizeof(real_t),
	      count * getVertexFormatData(_vertexFormat).vertDim * sizeof(real_t),
	      verts);
}

void VertexBuffer::writeColors(size_t offset,
                               size_t count,
                               const real_t* colors)
{
	ASSERT(getVertexFormatData(_vertexFormat).colorDim != 0,
	       "Vertices don't store colors");

	write(size_t(startOf(VertexFormatFlag::COLOR_FLAG))
	      + offset * getVertexFormatData(_vertexFormat).colorDim * sizeof(real_t),
	      count * getVertexFormatData(_vertexFormat).colorDim * sizeof(real_t),
	      colors);
}

void VertexBuffer::writeTextureCoords(size_t offset,
                                      size_t count,
                                      const real_t* texCoords)
{
	ASSERT(getVertexFormatData(_vertexFormat).textDim != 0,
	       "Vertices don't store texture coordinates");

	write(size_t(startOf(VertexFormatFlag::TEXT_FLAG))
	      + offset * getVertexFormatData(_vertexFormat).textDim * sizeof(real_t),
	      count * getVertexFormatData(_vertexFormat).textDim * sizeof(real_t),
	      texCoords);
}

void VertexBuffer::writeNormals(size_t offset,
                                size_t count,
                                const real_t* normals)
{
	ASSERT(getVertexFormatData(_vertexFormat).normalDim != 0,
	       "Vertices don't store normal coordinates");

	write(size_t(startOf(VertexFormatFlag::NORMAL_FLAG))
	      + offset * getVertexFormatData(_vertexFormat).normalDim * sizeof(real_t),
	      count * getVertexFormatData(_vertexFormat).normalDim * sizeof(real_t),
	      normals);
}

void VertexBuffer::draw(Primitive primitive,
                        size_t start,
                        size_t end)
{
	gl::bindBuffer(GL_ARRAY_BUFFER, _bufferID);

	const VertexFormatData& formatData = getVertexFormatData(_vertexFormat);
	enableVertexFormats(formatData);

	setArrays(formatData);

	glDrawArrays(GLenum(primitive), start, end);

	gl::bindBuffer(GL_ARRAY_BUFFER, 0);
	disableVertexFormats(formatData);
}

void VertexBuffer::draw(Primitive primitive)
{
	draw(primitive, 0, _vertexCount);
}

void VertexBuffer::draw(Primitive primitive,
                        IndexBuffer& indices)
{
	gl::bindBuffer(GL_ARRAY_BUFFER, _bufferID);
	gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices._bufferID);

	const VertexFormatData& formatData = getVertexFormatData(_vertexFormat);
	enableVertexFormats(formatData);

	setArrays(formatData);

	glDrawElements(GLenum(primitive),
	               indices._indexCount,
	               INDEX_TYPE,
	               0);

	gl::bindBuffer(GL_ARRAY_BUFFER, 0);
	gl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	disableVertexFormats(formatData);
}


void VertexBuffer::write(size_t offset,
                         size_t size,
                         const real_t* verts)
{
	ASSERT(_bufferID != 0,
	       "Buffer is invalid.");
	ASSERT(offset + size <= _vertexCount * getVertexFormatData(_vertexFormat).size * sizeof(real_t),
	       "Buffer overflow.");

	gl::bindBuffer(GL_ARRAY_BUFFER, _bufferID);
	gl::bufferSubData(GL_ARRAY_BUFFER,
	                  offset,
	                  size,
	                  verts);
	gl::bindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setArrays(const VertexFormatData& formatData)
{
	if (formatData.fmtFlags & VertexFormatFlag::VERT_FLAG)
	{
		gl::vertexPointer(formatData.vertDim,
		                  REAL_TYPE,
		                  0,
		                  startOf(VertexFormatFlag::VERT_FLAG));
	}

	if (formatData.fmtFlags & VertexFormatFlag::COLOR_FLAG)
	{
		gl::colorPointer(formatData.colorDim,
	  	                 REAL_TYPE,
		                 0,
		                 startOf(VertexFormatFlag::COLOR_FLAG));
	}

	if (formatData.fmtFlags & VertexFormatFlag::TEXT_FLAG)
	{
		gl::texCoordPointer(formatData.textDim,
		                    REAL_TYPE,
		                    0,
		                    startOf(VertexFormatFlag::TEXT_FLAG));
	}

	if (formatData.fmtFlags & VertexFormatFlag::NORMAL_FLAG)
	{
		ASSERT(formatData.normalDim == 3,
		       "Bad normal dimension");
		gl::normalPointer(REAL_TYPE,
		                  0,
		                  startOf(VertexFormatFlag::NORMAL_FLAG));
	}
}

const void* VertexBuffer::startOf(VertexFormatFlag type) const
{
	const VertexFormatData& formatData = getVertexFormatData(_vertexFormat);

	switch (type)
	{
		case VertexFormatFlag::VERT_FLAG:
			return 0;

		case VertexFormatFlag::COLOR_FLAG:
			return (void*) (_vertexCount
			                * formatData.vertDim
			                * sizeof(real_t));

		case VertexFormatFlag::TEXT_FLAG:
			return (void*) (_vertexCount
			                * (formatData.vertDim
			                   + formatData.colorDim)
			                * sizeof(real_t));

		case VertexFormatFlag::NORMAL_FLAG:
			return (void*) (_vertexCount
			                * (formatData.vertDim
			                   + formatData.colorDim
			                   + formatData.textDim)
			                * sizeof(real_t));
	}

	ASSERT(false,
	       "Parameter isn't of type VertexFormatFlag");

	return (void*) 0;
}

size_t VertexBuffer::getVertexCount() const
{
	return _vertexCount;
}

VertexFormat VertexBuffer::getVertexFormat() const
{
	return _vertexFormat;
}

BufferUsage VertexBuffer::getBufferUsage() const
{
	return _usage;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other)
{
	if (_bufferID != 0)
		gl::deleteBuffers(1, &_bufferID);

	_bufferID = other._bufferID;
	_vertexCount = other._vertexCount;
	_vertexFormat = other._vertexFormat;
	_usage = other._usage;

	other._bufferID = 0;
	other._vertexCount = 0;

	return *this;
}

bool VertexBuffer::isEmpty() const
{
	return _vertexCount == 0;
}

}
