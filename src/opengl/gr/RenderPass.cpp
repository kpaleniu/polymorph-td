/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/RenderPass.hpp"
#include "gr/opengl.hpp"

namespace gr {

RenderPass::RenderPass(BufferManager& bufferManager,
                       VertexFormat format,
                       Primitive shape,
                       const MaterialDesc& materialDesc,
                       const BufferDesc& bufferDesc,
                       const TransformDesc& transformDesc)
:	_bufferManager(bufferManager),
 	_shape(shape),
 	_vertices(bufferManager, format, BufferUsage::DYNAMIC),
 	_indices(BufferUsage::DYNAMIC),
 	_vertexWriter(_vertices, _indices),
 	_materialDesc(materialDesc),
 	_bufferDesc(bufferDesc),
 	_transformDesc(transformDesc),
 	_vertexSuppliers(),
 	_preRenderHook(),
 	_postRenderHook()
{
}

RenderPass::VertexSupplierHandle RenderPass::addVertexSupplier(VertexSupplier& vertexSupplier)
{
	return VertexSupplierHandle(_vertexSuppliers.insert(_vertexSuppliers.end(), &vertexSupplier));
}

void RenderPass::removeVertexSupplier(VertexSupplierHandle handle)
{
	_vertexSuppliers.erase((vertex_supplier_iterator) handle);
}

void RenderPass::render()
{
	updateVertices();

	if (_preRenderHook)
		_preRenderHook();

	if ( _bufferDesc.clearFlags != enum_t(BufferFlag::NONE) )
		glClear( GLenum(_bufferDesc.clearFlags) );

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(_transformDesc.projection.data());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(_transformDesc.view.data());
	glMultMatrixf(_transformDesc.model.data());

	if (_materialDesc.texture != nullptr)
	{
		// TODO Implement
	}
	if (_materialDesc.shader != nullptr)
	{
		// TODO Implement
	}

	if ( !_vertices.isEmpty() )
		_vertices.draw(_shape, _indices);

	if (_postRenderHook)
		_postRenderHook();
}

void RenderPass::preRender(Hook hook)
{
	_preRenderHook = hook;
}

void RenderPass::postRender(Hook hook)
{
	_postRenderHook = hook;
}


void RenderPass::updateVertices()
{
	for (auto supplier : _vertexSuppliers)
		supplier->writeVertices(_vertexWriter);

	_vertexWriter.flush();
}

}
