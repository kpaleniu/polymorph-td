#ifndef GR_MODEL_HPP_
#define GR_MODEL_HPP_

#include "gr/Mesh.hpp"
#include "gr/MeshManager.hpp"
#include "gr/Renderer.hpp"
#include "gr/types.hpp"

#include <NonCopyable.hpp>

#include <vector>

namespace gr {

class Model : NonCopyable
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

	/**
	 * Clones this model prototype.
	 *
	 * Note: This does not clone the meshes.
	 */
	Model cloneModelType() const;

	Transform& transform()				{ return _transform; }
	const Transform& transform() const	{ return _transform; }

private:
	std::vector<ModelMesh> _modelMeshes;
	Transform _transform;
};


}


#endif