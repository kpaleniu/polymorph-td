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
 * Mesh composition.
 *
 * 2D vertices are treated as on z=0 plane.
 */
class Model
{
public:
	struct ModelMesh
	{
		Transform transform;
		MeshManager::MeshHandle mesh;
	};


	Model(std::vector<ModelMesh>&& modelMeshes,
		  const Transform& transform = Transform());

	Model(Model&& other);

	void render(Renderer& renderer) const;
	void render(Renderer& renderer, const Transform& parentTransform) const;

	Transform& transform()				{ return _transform; }
	const Transform& transform() const	{ return _transform; }

	bool insideBoundBox(const MapVector2_r& p) const;
	bool insideBoundBox(const MapVector3_r& p) const;
	bool insideBoundBox(const MapVector_r& p) const;

private:
	std::vector<ModelMesh>	_modelMeshes;
	Transform				_transform;
	const AABox				_localBounds; // Must be initialized after _modelMeshes.
};


}


#endif