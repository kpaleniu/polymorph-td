/**
 * @file VertexArray.hpp
 *
 */

#ifndef VERTEXARRAY_HPP_
#define VERTEXARRAY_HPP_

namespace gr {

/**
 * Vertex array class.
 *
 * TODO Implement.
 */
class VertexArray
{
public:
	struct Format;
	struct Type;

	/**
	 * Constructor.
	 *
	 * @param dim 		dimension of vertices.
	 * @param format 	format of data.
	 * @param type		array type.
	 * @param data		vertex data.
	 */
	VertexArray(int dim,
	            Format format,
	            Type type,
	            void *data);

	~VertexArray();

public:
	struct Format
	{
		enum DataType
		{
			SHORT, INT, FLOAT, DOUBLE,
		} dataType;

		int stride;
	};

	struct Type
	{
		enum
		{
			COORD, TEX_COORD, NORMAL, COLOR,
		} type;
	};

private:
	Format _format;
	Type _type;

};

}

#endif /* VERTEXARRAY_HPP_ */
