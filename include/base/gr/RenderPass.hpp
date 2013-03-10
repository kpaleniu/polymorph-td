/**
 * @file RenderPass.hpp
 *
 */

#ifndef RENDERPASS_HPP_
#define RENDERPASS_HPP_

#include "gr/types.hpp"
#include "gr/VertexBuffer.hpp"
#include "gr/IndexBuffer.hpp"
#include "gr/BufferManager.hpp"
#include "gr/VertexSupplier.hpp"
#include "gr/Texture.hpp"
#include "gr/Shader.hpp"

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <functional>
#include <list>

namespace gr {

class RenderPass : NonCopyable
{
public:
	typedef std::list<VertexSupplier*>::iterator vertex_supplier_iterator;

	class VertexSupplierHandle : public PrivateHandle<vertex_supplier_iterator>
	{
		VertexSupplierHandle () : PrivateHandle<vertex_supplier_iterator>() {}
		VertexSupplierHandle (const vertex_supplier_iterator& v) : PrivateHandle<vertex_supplier_iterator>(v) {}

#ifdef TEST_BUILD
		vertex_supplier_iterator getVal() { return _val; }
#endif

		friend class RenderPass;
	};

	typedef std::function<void (RenderPass&)> Hook;

public:
	struct BufferDesc
	{
		enum_t useFlags;
		enum_t clearFlags;
	};

	struct TransformDesc
	{
		TransformDesc(Projection p, Transform m, Transform v)
		:	projection(p),
			model(m),
			view(v)
		{}

		Projection projection;
		Transform model;
		Transform view;
	};

	struct MaterialDesc
	{
		const Texture* texture;
		const Shader*  shader;
	};

	RenderPass( VertexFormat format,
	            Primitive shape,
			    MaterialDesc materialDesc,
	            BufferDesc bufferDesc,
	            const TransformDesc& transformDesc );

	RenderPass(RenderPass&& other);

	VertexSupplierHandle addVertexSupplier(VertexSupplier& vertexSupplier);
	void removeVertexSupplier(VertexSupplierHandle handle);
	void clearVertexSuppliers();

	void updateVertices();
	void render();

	void preRender(Hook hook);
	void postRender(Hook hook);

	ModelVector unProject(const ClipVector& ndcVec) const;
	ClipVector project(const ModelVector& modelVec) const;

	void setProjection(const Projection& projection);
	void setModelTransform(const Transform& modelTransform);
	void setViewTransform(const Transform& viewTransform);

	void setTexture(const Texture* tex);
	void setShader(const Shader* shader);

private:
	Primitive _shape;

	VertexBuffer _vertices;
	IndexBuffer _indices;

	VertexWriter _vertexWriter;

	MaterialDesc 	_materialDesc;
	BufferDesc 		_bufferDesc;
	TransformDesc 	_transformDesc;
	TransformDesc	_invTransformDesc;

	std::list<VertexSupplier*> _vertexSuppliers;

	Hook _preRenderHook;
	Hook _postRenderHook;

	bool _needUpdate;
};

}


#endif /* RENDERPASS_HPP_ */
