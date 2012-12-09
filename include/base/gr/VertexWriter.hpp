


#ifndef VERTEXWRITER_HPP
#define VERTEXWRITER_HPP

#include "gr/VertexBuffer.hpp"
#include "gr/IndexBuffer.hpp"

#include <vector>

namespace gr {

class VertexWriter
{
public:
	template<typename T>
	class DataWriter
	{
	public:
		DataWriter(std::vector<T>& dataSource);
		DataWriter<T>& operator<<(const std::vector<T>& data);

		// To avoid re-writing constant data (not able to do this with current implementation).
		//VertexWriter& keep(size_t vertexCount, size_t vertexCount);

	private:
		std::vector<T>& _dataSource;
	};

public:
	VertexWriter(VertexBuffer& vertices, IndexBuffer& indices);

	DataWriter<real_t>& vertices();
	DataWriter<real_t>& colors();
	DataWriter<real_t>& texCoords();
	DataWriter<real_t>& normals();
	DataWriter<index_t>& indices();

	/**
	 * Writes the vertices to the Vertex- and IndexBuffer
	 * and resets the write position to the start.
	 *
	 * This should be called once per frame.
	 */
	void flush();

private:
	VertexBuffer& _vertices;
	IndexBuffer&  _indices;

	std::vector<real_t>  _vertBuffer;
	std::vector<real_t>  _colorBuffer;
	std::vector<real_t>  _texCoordBuffer;
	std::vector<real_t>  _normalBuffer;
	std::vector<index_t> _indexBuffer;

	DataWriter<real_t> _vertexWriter;
	DataWriter<real_t> _colorWriter;
	DataWriter<real_t> _texCoordWriter;
	DataWriter<real_t> _normalWriter;
	DataWriter<index_t> _indexWriter;
};

//

inline VertexWriter::DataWriter<real_t>& VertexWriter::vertices()
{
	return _vertexWriter;
}

inline VertexWriter::DataWriter<real_t>& VertexWriter::colors()
{
	return _colorWriter;
}

inline VertexWriter::DataWriter<real_t>& VertexWriter::texCoords()
{
	return _texCoordWriter;
}

inline VertexWriter::DataWriter<real_t>& VertexWriter::normals()
{
	return _normalWriter;
}

inline VertexWriter::DataWriter<index_t>& VertexWriter::indices()
{
	return _indexWriter;
}
//

template<typename T>
VertexWriter::DataWriter<T>::DataWriter(std::vector<T>& dataSource)
:	_dataSource(dataSource)
{
}

template<typename T>
VertexWriter::DataWriter<T>& VertexWriter::DataWriter<T>::operator<<(const std::vector<T>& vertices)
{
	for (auto real : vertices)
		_dataSource.push_back(real);
	return *this;
}

}


#endif