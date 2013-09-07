#ifndef GR_MODEL_HPP_
#define GR_MODEL_HPP_

#include "gr/Mesh.hpp"
#include "gr/MeshManager.hpp"
#include "gr/Renderer.hpp"
#include "gr/types.hpp"

#include <NonCopyable.hpp>

#include <vector>

namespace gr {

template <typename TransformType = Transform3>
class Model : NonCopyable
{
public:
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