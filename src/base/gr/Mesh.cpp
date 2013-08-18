#include "gr/Mesh.hpp"

#include <algorithm>

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

void Mesh::SubMesh::render(Renderer& renderer, 
						   index_t meshStartIndex) const
{
	auto& passManager = renderer.renderPassManager();

	std::vector<index_t> transformedIndices(_indices);
	for (index_t& index : transformedIndices)
		index += meshStartIndex;

	auto indexWriter =
		passManager.indexWriter(_parent._vertexList.format,
								_parent._shape,
								_texHandle,
								nullptr);

	indexWriter.write(transformedIndices.data(),
					  transformedIndices.size());
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
		_subMeshes.push_back(
			SubMesh(*this, 
				    subMesh._texHandle, 
					std::move(subMesh._indices)));
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
	auto& passManager = renderer.renderPassManager();
	auto vertexWriter = 
		passManager.vertexWriter(_vertexList.format);

	vertexWriter.writeVertexData(_vertexList);


	for (const auto& subMesh : _subMeshes)
		subMesh.render(renderer, vertexWriter.startIndex());
}

void Mesh::render(Renderer& renderer, 
				  const Transform& transform) const
{
	auto& passManager = renderer.renderPassManager();
	auto vertexWriter =
		passManager.vertexWriter(_vertexList.format);

	const VertexFormatData& fmtData =
		getVertexFormatData(_vertexList.format);

	ASSERT(fmtData.vertDim < 5,
		   "Vertex dimension not supported.");


	real_t buffVec[4];
	
	for (index_t i = 0; i < _vertexList.vertexCount(); ++i)
	{
		const real_t* vertices = _vertexList.vertexData(i);

		// const MapVector_r will not modify the data.
		const MapVector_r mapVec(const_cast<real_t*>(vertices), 
								 fmtData.vertDim);

		MapVector_r bufVec(buffVec, fmtData.vertDim);
		bufVec = mapVec;

		transform.transform(bufVec);

		vertexWriter.vertices().write(bufVec.data(), 
									  bufVec.rows());
	}

	for (const auto& subMesh : _subMeshes)
		subMesh.render(renderer, vertexWriter.startIndex());
}

const VertexList& Mesh::vertices() const
{
	return _vertexList;
}

}