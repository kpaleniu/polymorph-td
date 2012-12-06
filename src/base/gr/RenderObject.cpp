/**
 * @file RenderObject.cpp
 *
 */

#include "gr/RenderObject.hpp"

namespace gr {

RenderObject::RenderObject(Material& material,
                           VertexSupplier& vertexSupplier)
:	_material(material),
 	_vertexSupplier(vertexSupplier)
{
}

Material& RenderObject::material()
{
	return _material;
}

}
