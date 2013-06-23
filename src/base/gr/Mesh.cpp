#include "gr/Mesh.hpp"


namespace gr {


// Mesh::SubMesh

Mesh::SubMesh::SubMesh(Mesh& parent, 
					   TextureManager::TextureHandle texHandle,
					   std::vector<index_t>&& indices)
:	_parent(parent),
	_texHandle(texHandle),
	_indices(std::move(indices))
{
}

Mesh::SubMesh::SubMesh(SubMesh&& other)
:	_parent(other._parent),
	_texHandle(other._texHandle),
	_indices(std::move(other._indices))
{
}

void Mesh::SubMesh::render(Renderer& renderer) const
{
	auto& vertexWriter = 
		renderer.renderPassManager().vertexWriter(_parent._vertexList.format, 
												  _parent._shape,
												  _texHandle,
												  nullptr);

	index_t startIndex = vertexWriter.getVertexCount();
	const VertexFormatData& fmtData = getVertexFormatData(_parent._vertexList.format);

	for (index_t index : _indices)
	{
		{
			const real_t* vertices = _parent._vertexList.vertexData(index);
			for (unsigned int i = 0; i < fmtData.vertDim; ++i)
				vertexWriter.vertices() << vertices[i];
		}

		{
			const real_t* colors = _parent._vertexList.colorData(index);
			for (unsigned int i = 0; i < fmtData.colorDim; ++i)
				vertexWriter.colors() << colors[i];
		}

		{
			const real_t* texCoords = _parent._vertexList.texCoordData(index);
			for (unsigned int i = 0; i < fmtData.textDim; ++i)
				vertexWriter.texCoords() << texCoords[i];
		}

		vertexWriter.indices() << (startIndex + index);
	}
}

void Mesh::SubMesh::render(Renderer& renderer, const Transform& transform) const
{
	real_t vertBuffer[4];

	auto& vertexWriter = 
		renderer.renderPassManager().vertexWriter(_parent._vertexList.format, 
												  _parent._shape,
												  _texHandle,
												  nullptr);

	index_t startIndex = vertexWriter.getVertexCount();
	const VertexFormatData& fmtData = getVertexFormatData(_parent._vertexList.format);

	ASSERT(fmtData.vertDim < 5, "Vertex dimension not supported.");

	for (index_t index : _indices)
	{
		{
			real_t* vertices = _parent._vertexList.vertexData(index);
			MapVector_r mapVec(vertices, fmtData.vertDim);

			MapVector_r bufVec(vertBuffer, fmtData.vertDim);
			bufVec = mapVec;

			transform.transform(bufVec);

			for (unsigned int i = 0; i < bufVec.rows(); ++i)
				vertexWriter.vertices() << bufVec[i];
		}

		{
			const real_t* colors = _parent._vertexList.colorData(index);
			for (unsigned int i = 0; i < fmtData.colorDim; ++i)
				vertexWriter.colors() << colors[i];
		}

		{
			const real_t* texCoords = _parent._vertexList.texCoordData(index);
			for (unsigned int i = 0; i < fmtData.textDim; ++i)
				vertexWriter.texCoords() << texCoords[i];
		}

		vertexWriter.indices() << (startIndex + index);
	}
}

// Mesh

Mesh::Mesh(VertexList&& vertices, Primitive shape)
:	_vertexList(std::move(vertices)),
	_subMeshes(),
	_shape(shape)
{
}

Mesh::Mesh(Mesh&& other)
:	_vertexList(std::move(other._vertexList)),
	_subMeshes(),
	_shape(other._shape)
{
	for (SubMesh& subMesh : other._subMeshes)
	{
		_subMeshes.push_back(SubMesh(*this, subMesh._texHandle, std::move(subMesh._indices)));
	}

	other._subMeshes.clear();
}

void Mesh::addSubMesh(TextureManager::TextureHandle texture,
					  std::vector<index_t>&& indices)
{
	_subMeshes.push_back(SubMesh(*this, texture, std::move(indices)));
}

void Mesh::render(Renderer& renderer) const
{
	for (const auto& subMesh : _subMeshes)
		subMesh.render(renderer);
}

void Mesh::render(Renderer& renderer, const Transform& transform) const
{
	for (const auto& subMesh : _subMeshes)
		subMesh.render(renderer, transform);
}

const VertexList& Mesh::vertices() const
{
	return _vertexList;
}

}