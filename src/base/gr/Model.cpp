#include "gr/Model.hpp"


namespace gr {


Model::Model(std::vector<ModelMesh>&& modelMeshes, const Transform& transform)
:	_modelMeshes(std::move(modelMeshes)),
	_transform(transform)
{
}

Model::Model(Model&& other)
:	_modelMeshes(std::move(other._modelMeshes)),
	_transform(other._transform)
{
}

void Model::render(Renderer& renderer) const
{
	for (const auto& modelMesh : _modelMeshes)
		modelMesh.mesh->render(renderer, _transform * modelMesh.transform);
}

void Model::render(Renderer& renderer, const Transform& parentTransform) const
{
	const auto& modelTransform = parentTransform * _transform;

	for (const auto& modelMesh : _modelMeshes)
		modelMesh.mesh->render(renderer, modelTransform * modelMesh.transform);
}

}