

#include "gr/VertexWriter.hpp"

#include <Assert.hpp>

namespace gr {

VertexWriter::VertexWriter(VertexBuffer& vertices,
                           IndexBuffer& indices)
:	_vertices(vertices),
 	_indices(indices),
 	_vertBuffer(),
 	_colorBuffer(),
 	_texCoordBuffer(),
 	_normalBuffer(),
 	_indexBuffer(),
 	_vertexWriter(_vertBuffer),
 	_colorWriter(_colorBuffer),
 	_texCoordWriter(_texCoordBuffer),
 	_normalWriter(_normalBuffer),
 	_indexWriter(_indexBuffer)
{
	auto formatFlags = getVertexFormatData(vertices.getVertexFormat());
	auto initialCount = vertices.getVertexCount();

	if (formatFlags.vertDim > 0)
		_vertBuffer.reserve(formatFlags.vertDim * initialCount);
	if (formatFlags.colorDim > 0)
		_colorBuffer.reserve(formatFlags.colorDim * initialCount);
	if (formatFlags.textDim > 0)
		_texCoordBuffer.reserve(formatFlags.textDim * initialCount);
	if (formatFlags.normalDim > 0)
		_normalBuffer.reserve(formatFlags.normalDim * initialCount);

	_indexBuffer.reserve(indices.getIndexCount());
}

void VertexWriter::flush()
{
	size_t newVertSize = 0;
	auto formatFlags = getVertexFormatData(_vertices.getVertexFormat());
	auto currentCount = _vertices.getVertexCount();
	auto indexCount = _indices.getIndexCount();

	// Checks if buffer needs resizing.

	if (formatFlags.vertDim > 0)
	{
		ASSERT(_vertBuffer.size() % formatFlags.vertDim == 0,
		       "Vertices in incorrect format.");

		size_t vertexCount = _vertBuffer.size() / formatFlags.vertDim;
		newVertSize = vertexCount;
	}
	if (formatFlags.colorDim > 0)
	{
		ASSERT(_colorBuffer.size() % formatFlags.colorDim == 0,
			   "Colors in incorrect format.");

		size_t colorCount = _colorBuffer.size() / formatFlags.colorDim;

		// Should be optimized to only resize if count is larger.
		if (newVertSize != 0)
		{
			ASSERT(colorCount == newVertSize,
			       "Bad color count");
		}

		newVertSize = colorCount;
	}
	if (formatFlags.textDim > 0)
	{
		ASSERT(_texCoordBuffer.size() % formatFlags.textDim == 0,
			   "Texture coordinates in incorrect format.");

		size_t texCoordCount = _texCoordBuffer.size() / formatFlags.textDim;

		// Should be optimized to only resize if count is larger.
		if (newVertSize != 0)
		{
			ASSERT(texCoordCount == newVertSize,
				   "Bad texture coordinate count");
		}
		newVertSize = texCoordCount;
	}
	if (formatFlags.normalDim > 0)
	{
		ASSERT(_normalBuffer.size() % formatFlags.normalDim == 0,
			   "Normal coordinates in incorrect format.");

		size_t normalCount = _normalBuffer.size() / formatFlags.normalDim;

		// Should be optimized to only resize if count is larger.
		if (newVertSize != 0)
		{
			ASSERT(normalCount == newVertSize,
				   "Bad normal count");
		}
		newVertSize = normalCount;
	}
	//

	// Resize buffers if needed.

	if (newVertSize != currentCount)
	{
		VertexBuffer newBuffer(_vertices.bufferManager(),
		                       _vertices.getVertexFormat(),
		                       _vertices.getBufferUsage(),
		                       newVertSize);
		_vertices = std::move(newBuffer);
	}
	if (indexCount != _indexBuffer.size())
	{
		IndexBuffer newBuffer(_indices.getBufferUsage(),
		                      _indexBuffer.size());
		_indices = std::move(newBuffer);
	}

	//

	if (newVertSize == 0)
		return;

	// Write data.

	if (formatFlags.vertDim > 0)
		_vertices.writeVertices(0, _vertBuffer.size() / formatFlags.vertDim, _vertBuffer.data());
	if (formatFlags.colorDim > 0)
		_vertices.writeColors(0, _colorBuffer.size() / formatFlags.colorDim, _colorBuffer.data());
	if (formatFlags.textDim > 0)
		_vertices.writeColors(0, _texCoordBuffer.size() / formatFlags.textDim, _texCoordBuffer.data());
	if (formatFlags.normalDim > 0)
		_vertices.writeColors(0, _normalBuffer.size() / formatFlags.normalDim, _normalBuffer.data());

	_indices.writeIndices(0, _indexBuffer.size(), _indexBuffer.data());

	//

	// Clear frame.

	_vertBuffer.clear();
	_colorBuffer.clear();
	_texCoordBuffer.clear();
	_normalBuffer.clear();
	_indexBuffer.clear();

	//
}

size_t VertexWriter::getVertexCount() const
{
	ASSERT(_vertBuffer.size() / getVertexFormatData(_vertices.getVertexFormat()).vertDim == 0,
	       "Vertex buffer is corrupt.");

	return _vertBuffer.size() / getVertexFormatData(_vertices.getVertexFormat()).vertDim;
}

}

