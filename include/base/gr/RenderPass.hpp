/**
 * @file RenderPass.hpp
 *
 */

#ifndef RENDERPASS_HPP_
#define RENDERPASS_HPP_

#include "gr/Material.hpp"
#include "gr/VertexBuffer.hpp"
#include "gr/IndexBuffer.hpp"
#include "gr/BufferManager.hpp"
#include "gr/VertexSupplier.hpp"

#include <PrivateHandle.hpp>

#include <list>

namespace gr {

class RenderPass
{
public:
	typedef std::list<VertexSupplier*>::iterator vertex_supplier_iterator;

	class VertexSupplierHandle : public PrivateHandle<vertex_supplier_iterator>
	{
		VertexSupplierHandle () : PrivateHandle<vertex_supplier_iterator>() {}
		VertexSupplierHandle (const vertex_supplier_iterator& v) : PrivateHandle<vertex_supplier_iterator>(v) {}

		friend class RenderPass;
	};


public:
	struct BufferDesc
	{
		enum_t useFlags;
		enum_t clearFlags;
	};

	struct TransformDesc
	{
		Projection projection;
		Transform model;
		Transform view;
	};

	struct MaterialDesc
	{
		Texture* texture;
		Shader*  shader;
	};

	RenderPass( BufferManager& bufferManager,
	            VertexFormat format,
	            Primitive shape = Primitive::TRIANGLES,
			    const MaterialDesc& materialDesc = {nullptr, nullptr},
	            const BufferDesc& bufferDesc = {enum_t(BufferFlag::ALL), enum_t(BufferFlag::ALL)},
	            const TransformDesc& transformDesc = {Projection::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f),
	                                                 Transform::identity(),
	                                                 Transform::identity()} );

	VertexSupplierHandle addVertexSupplier(VertexSupplier& vertexSupplier);
	void removeVertexSupplier(VertexSupplierHandle handle);

	void render();

private:
	void updateVertices();

	BufferManager& _bufferManager;

	Primitive _shape;

	VertexBuffer _vertices;
	IndexBuffer _indices;

	VertexWriter _vertexWriter;

	const MaterialDesc& 	_materialDesc;
	const BufferDesc& 		_bufferDesc;
	const TransformDesc& 	_transformDesc;

	std::list<VertexSupplier*> _vertexSuppliers;
};

}


#endif /* RENDERPASS_HPP_ */
