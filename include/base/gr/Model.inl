#include "gr/Model.hpp"

#include <Debug.hpp>

#include <limits>
#include <algorithm>

namespace polymorph { namespace gr {

namespace detail {

template <typename TransformType>
AABox createBoundingBox(const std::vector<typename Model<TransformType>::ModelMesh>& meshes)
{
	if (meshes.empty())
		return AABox(0, 0, 0, 0, 0, 0);

	real_t
		minX = std::numeric_limits<real_t>::infinity(),
		minY = std::numeric_limits<real_t>::infinity(),
		minZ = std::numeric_limits<real_t>::infinity(),
		maxX = -std::numeric_limits<real_t>::infinity(),
		maxY = -std::numeric_limits<real_t>::infinity(),
		maxZ = -std::numeric_limits<real_t>::infinity();

	for (const auto& modelMesh : meshes)
	{
		const Mesh& mesh = *modelMesh.mesh;

		const auto& vList = mesh.vertices();
		const auto& vertexFmtData = getVertexFormatData(vList.format);

		for (std::size_t i = 0; i < mesh.vertices().vertexCount(); ++i)
		{
			// TODO Apply transformation.

			real_t x, y, z = 0;

			const real_t* v = vList.vertexData(i);

			x = v[0];
			y = v[1];

			if (vertexFmtData.vertDim >= 3)
				z = v[2];

			minX = std::min(minX, x);
			minY = std::min(minY, y);
			minZ = std::min(minZ, z);
			maxX = std::max(maxX, x);
			maxY = std::max(maxY, y);
			maxZ = std::max(maxZ, z);
		}
	}

	return AABox(minX, minY, minZ, maxX, maxY, maxZ);
}

}

template <typename TransformType>
Model<TransformType>::Model(std::vector<ModelMesh>&& modelMeshes, 
							unsigned int mask,
							const TransformType& transform)
:	 _modelMeshes(std::move(modelMeshes)),
	_mask(mask),
	_transform(transform),
	_localBounds(detail::createBoundingBox<TransformType>(_modelMeshes))
{
}

template <typename TransformType>
Model<TransformType>::Model(Model<TransformType>&& other)
:	_modelMeshes(std::move(other._modelMeshes)),
	_mask(other._mask),
	_transform(other._transform),
	_localBounds(other._localBounds)
{
}

template <typename TransformType>
void Model<TransformType>::render(Renderer& renderer) const
{
	for (const auto& modelMesh : _modelMeshes)
		modelMesh.mesh->render(renderer, _transform * modelMesh.transform);
}

template <typename TransformType>
void Model<TransformType>::render(Renderer& renderer, 
								  const TransformType& parentTransform) const
{
	const auto& modelTransform = parentTransform * _transform;

	for (const auto& modelMesh : _modelMeshes)
		modelMesh.mesh->render(renderer, modelTransform * modelMesh.transform);
}

template <typename TransformType>
unsigned int Model<TransformType>::mask() const
{
	return _mask;
}

template <typename TransformType>
TransformType& Model<TransformType>::transform()
{
	return _transform;
}

template <typename TransformType>
const TransformType& Model<TransformType>::transform() const
{
	return _transform;
}

template <typename TransformType>
bool Model<TransformType>::insideBoundBox(const MapVector2_r& p) const
{
	const auto& localSpaceVec2 = _transform * p;

	return _localBounds.inside(localSpaceVec2[0], localSpaceVec2[1], 0);
}

template <typename TransformType>
bool Model<TransformType>::insideBoundBox(const MapVector3_r& p) const
{
	const auto& localSpaceVec3 = _transform * p;

	return _localBounds.inside(localSpaceVec3);
}

template <typename TransformType>
bool Model<TransformType>::insideBoundBox(const MapVector_r& p) const
{
	real_t buffer[4];
	ASSERT(p.rows() < 5, "Unsupported vector size.");

	MapVector_r bufVec(buffer, p.rows());
	bufVec = p;

	_transform.transform(bufVec);

	real_t x = bufVec[0];
	real_t y = bufVec[1];
	real_t z = bufVec.rows() >= 3 ? bufVec[2] : 0.0f;

	return _localBounds.inside(x, y, z);
}


} }