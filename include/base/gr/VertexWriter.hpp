#ifndef VERTEXWRITER_HPP
#define VERTEXWRITER_HPP

#include "gr/VertexBuffer.hpp"
#include "gr/IndexBuffer.hpp"
#include "gr/VertexList.hpp"

#include <NonCopyable.hpp>

#include <vector>

namespace gr {

class VertexSource : NonCopyable
{
public:
	VertexSource(VertexFormat format_);
	VertexSource(VertexSource&& other);

	VertexFormat format;

	std::vector<real_t> vertices;
	std::vector<real_t> colors;
	std::vector<real_t> texCoords;
	std::vector<real_t> normals;

	void clear();
};

/**
 * Interface for writing vertices to a vertex source 
 * and index source.
 */
class VertexWriter
{
public:
	class DataWriter : NonCopyable
	{
	public:
		DataWriter(std::vector<real_t>& dataSource);

		DataWriter& operator<<(real_t data);
		DataWriter& write(const real_t* data, 
						  std::size_t size);

	private:
		std::vector<real_t>& _dataSource;
	};


public:
	VertexWriter(VertexSource& writeTarget);

	DataWriter& vertices();
	DataWriter& colors();
	DataWriter& texCoords();
	DataWriter& normals();

	void writeVertexData(const VertexList& vl);

	index_t startIndex() const;

private:
	DataWriter _vertexWriter;
	DataWriter _colorWriter;
	DataWriter _texCoordWriter;
	DataWriter _normalWriter;

	const index_t _startIndex;
};

class IndexWriter : NonCopyable
{
public:
	IndexWriter(std::vector<index_t>& indexSource);

	IndexWriter& operator<<(index_t data);
	IndexWriter& write(const index_t* data,
					   std::size_t size);

private:
	std::vector<index_t>& _indexSource;
};

}


#endif
