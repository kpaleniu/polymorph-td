/**
 * @file VertexSupplier.hpp
 *
 */

#ifndef VERTEXSUPPLIER_HPP_
#define VERTEXSUPPLIER_HPP_

#include "gr/VertexWriter.hpp"

namespace gr {

class VertexSupplier
{
public:
	virtual ~VertexSupplier() {};

	virtual void writeVertices(VertexWriter&) = 0;
};

}


#endif /* VERTEXSUPPLIER_HPP_ */
