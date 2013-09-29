#pragma once

#include "gr/Mesh.hpp"
#include "gr/MeshManager.hpp"
#include "gr/Renderer.hpp"
#include "gr/types.hpp"

#include <NonCopyable.hpp>

#include <vector>

namespace polymorph { namespace gr {

/**
 * Mesh composition class.
 *
 * A model is a composition of meshes with local transformations
 * as well as an own transformation.
 *
 * Note, this class is not sutable for static terrain (i.e.
 * where transformations are expected to be constant). This is due
 * to the fact that the meshes local transformation will be 
 * generated with every render call.
 */
template <typename TransformType = Transform3>
class Model
{
public:

	/**
	 * Local transformation (in model space) - mesh pair.
	 */
	struct ModelMesh
	{
		TransformType transform;
		MeshManager::Handle mesh;
	};


	Model(std::vector<ModelMesh>&& modelMeshes,
		  unsigned int mask = 0,
		  const TransformType& transform = TransformType());

	Model(Model&& other);

	void render(Renderer& renderer) const;
	void render(Renderer& renderer, const TransformType& parentTransform) const;

	unsigned int mask() const;

	TransformType& transform();
	const TransformType& transform() const;

	bool insideBoundBox(const MapVector2_r& p) const;
	bool insideBoundBox(const MapVector3_r& p) const;
	bool insideBoundBox(const MapVector_r& p) const;

private:
	std::vector<ModelMesh>	_modelMeshes;
	unsigned int			_mask;
	TransformType			_transform;
	AABox				_localBounds; // Must be initialized after _modelMeshes.
};


} }

#include "gr/Model.inl"