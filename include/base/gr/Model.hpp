#ifndef GR_MODEL_HPP_
#define GR_MODEL_HPP_

#include "gr/Mesh.hpp"
#include "gr/MeshManager.hpp"
#include "gr/Renderer.hpp"
#include "gr/types.hpp"

#include <NonCopyable.hpp>

#include <vector>

namespace gr {

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
class Model : NonCopyable
{
public:

	/**
	 * Local transformation (in model space) - mesh pair.
	 */
	struct ModelMesh
	{
		TransformType transform;
		MeshManager::MeshHandle mesh;
	};


	Model(std::vector<ModelMesh>&& modelMeshes,
		  const TransformType& transform = TransformType());

	Model(Model&& other);

	void render(Renderer& renderer) const;
	void render(Renderer& renderer, const TransformType& parentTransform) const;

	TransformType& transform();
	const TransformType& transform() const;

	bool insideBoundBox(const MapVector2_r& p) const;
	bool insideBoundBox(const MapVector3_r& p) const;
	bool insideBoundBox(const MapVector_r& p) const;

private:
	std::vector<ModelMesh>	_modelMeshes;
	TransformType			_transform;
	const AABox				_localBounds; // Must be initialized after _modelMeshes.
};


}

#include "gr/Model.inl"

#endif