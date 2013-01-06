/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/RenderPass.hpp"
#include "gr/opengl.hpp"
#include "gr/Texture.hpp"

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
 	_postRenderHook(),
 	_needUpdate(true)
{
}

RenderPass::RenderPass(RenderPass&& other)
:	_bufferManager(other._bufferManager),
 	_shape(other._shape),
 	_vertices(std::move(other._vertices)),
 	_indices(std::move(other._indices)),
 	_vertexWriter(_vertices, _indices),
 	_materialDesc(other._materialDesc),
 	_bufferDesc(other._bufferDesc),
 	_transformDesc(other._transformDesc),
 	_vertexSuppliers(std::move(other._vertexSuppliers)),
 	_preRenderHook(other._preRenderHook),
 	_postRenderHook(other._postRenderHook),
 	_needUpdate(other._needUpdate)
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
	if (_needUpdate)
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
		glEnable(GL_TEXTURE_2D);
		_materialDesc.texture->bind();
	}

	if (_materialDesc.shader != nullptr)
	{
		// TODO Implement
	}

	if ( !_vertices.isEmpty() )
		_vertices.draw(_shape, _indices);

	if (_materialDesc.texture != nullptr)
	{
		_materialDesc.texture->unbind();
		glDisable(GL_TEXTURE_2D);
	}

	if (_postRenderHook)
		_postRenderHook();

	_needUpdate = true;
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

	_needUpdate = false;
}

}
