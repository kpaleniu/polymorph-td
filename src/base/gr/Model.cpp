#include "gr/Model.hpp"


namespace gr {


Model::Model(std::vector<ModelMesh>&& modelMeshes, const Transform& transform)
:	_modelMeshes(std::move(modelMeshes)),
	_transform(transform)
{
}


void Model::render(Renderer& renderer) const
{
	for (const auto& modelMesh : _modelMeshes)
		modelMesh.mesh->render(renderer, _transform * modelMesh.transform);
}


}