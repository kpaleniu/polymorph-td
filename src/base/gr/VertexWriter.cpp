#include "gr/VertexWriter.hpp"

#include <Assert.hpp>

namespace polymorph { namespace gr {

namespace {

index_t getVertexCount(VertexSource& source)
{
	auto fmtData = getVertexFormatData(source.format);

	ASSERT(source.vertices.size() % fmtData.vertDim == 0,
		   "Bad vertex source");

	return source.vertices.size() / fmtData.vertDim;
}

}


VertexSource::VertexSource(VertexFormat format_)
:	format(format_),
	vertices(), 
	colors(),
	texCoords(), 
	normals()
{
}

VertexSource::VertexSource(VertexSource&& other)
:	format(other.format),
	vertices(std::move(other.vertices)),
	colors(std::move(other.colors)),
	texCoords(std::move(other.texCoords)),
	normals(std::move(other.normals))
{
}

void VertexSource::clear()
{
	vertices.clear();
	colors.clear();
	texCoords.clear();
	normals.clear();
}

// VertexWriter

VertexWriter::VertexWriter(VertexSource& writeTarget)
:	_vertexWriter(writeTarget.vertices),
 	_colorWriter(writeTarget.colors),
 	_texCoordWriter(writeTarget.texCoords),
 	_normalWriter(writeTarget.normals),
	_startIndex(getVertexCount(writeTarget))
{
}

VertexWriter::DataWriter& VertexWriter::vertices()
{
	return _vertexWriter;
}

VertexWriter::DataWriter& VertexWriter::colors()
{
	return _colorWriter;
}

VertexWriter::DataWriter& VertexWriter::texCoords()
{
	return _texCoordWriter;
}

VertexWriter::DataWriter& VertexWriter::normals()
{
	return _normalWriter;
}

void VertexWriter::writeVertexData(const VertexList& vl)
{
	_vertexWriter.write(vl.vertices.data(),
						vl.vertices.size());
	
	_colorWriter.write(vl.colors.data(),
					   vl.colors.size());

	_texCoordWriter.write(vl.texCoords.data(),
						  vl.texCoords.size());

	// _normalWriter.write(v) // Forgot to implement normals...
}

index_t VertexWriter::startIndex() const
{
	return _startIndex;
}

// DataWriter:

VertexWriter::DataWriter::DataWriter(std::vector<real_t>& dataSource)
:	_dataSource(dataSource)
{
}

VertexWriter::DataWriter& VertexWriter::DataWriter::operator<<(real_t data)
{
	_dataSource.push_back(data);
	
	return *this;
}

VertexWriter::DataWriter& VertexWriter::DataWriter::write(const real_t* data,
														  std::size_t size)
{
	for (std::size_t i = 0; i < size; ++i)
		_dataSource.push_back(data[i]);
	
	return *this;
}

// IndexWriter

IndexWriter::IndexWriter(std::vector<index_t>& indexSource)
:	_indexSource(indexSource)
{
}

IndexWriter& IndexWriter::operator<<(index_t data)
{
	_indexSource.push_back(data);

	return *this;
}

IndexWriter& IndexWriter::write(const index_t* data,
								 std::size_t size)
{
	for (std::size_t i = 0; i < size; ++i)
		_indexSource.push_back(data[i]);

	return *this;
}

} }