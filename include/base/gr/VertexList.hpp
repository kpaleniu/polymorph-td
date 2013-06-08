#ifndef GR_VERTEX_LIST_HPP_
#define GR_VERTEX_LIST_HPP_


#include "gr/types.hpp"
#include "gr/VertexFormat.hpp"

#include <NonCopyable.hpp>

#include <vector>


namespace gr {

struct VertexList : NonCopyable
{
	VertexList(VertexFormat format_, 
			   std::vector<real_t>&& vertices_, 
			   std::vector<real_t>&& colors_ = std::vector<real_t>(),
			   std::vector<real_t>&& texCoords_ = std::vector<real_t>());

	VertexList(VertexList&& other);


	// Returns nullptr if don't store that data type:

	real_t* vertexData(index_t vertIndex); // Never returns nullptr.
	real_t* colorData(index_t vertIndex);
	real_t* texCoordData(index_t vertIndex);
	
	const real_t* vertexData(index_t vertIndex) const; // Never returns nullptr.
	const real_t* colorData(index_t vertIndex) const;
	const real_t* texCoordData(index_t vertIndex) const;

	//

	std::size_t vertexCount() const;

	VertexFormat format;

	std::vector<real_t> vertices;
	std::vector<real_t> colors;
	std::vector<real_t> texCoords;
	// std::vector<real_t> normals; // Variation not implemented in VertexFormat.
};

}


#endif