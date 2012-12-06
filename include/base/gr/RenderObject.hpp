/**
 * @file RenderObject.hpp
 *
 */

#ifndef RENDEROBJECT_HPP_
#define RENDEROBJECT_HPP_

#include "gr/VertexSupplier.hpp"
#include "gr/Material.hpp"

namespace gr {

class RenderObject
{
public:
	RenderObject(Material& material, VertexSupplier& vertexSupplier);

	Material& material();

private:
	Material _material;
	VertexSupplier& _vertexSupplier;
};

}

#endif /* RENDEROBJECT_HPP_ */
