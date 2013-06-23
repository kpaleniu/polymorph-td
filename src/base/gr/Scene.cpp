#include "gr/Scene.hpp"

#include <Debug.hpp>

namespace gr {

Scene::Scene()
:	_modelRegister()
{
}

Scene::Scene(Scene&& other)
:	_modelRegister(std::move(other._modelRegister))
{
}

void Scene::addModel(model_id id, Model&& model)
{
	ASSERT(_modelRegister.find(id) == _modelRegister.end(), "Trying to overwrite model in scene.");

	_modelRegister.insert(std::make_pair(id, std::move(model)));
}

void Scene::removeModel(model_id id)
{
	ASSERT(_modelRegister.find(id) != _modelRegister.end(), "Trying to remove non-existing model.");

	_modelRegister.erase(id);
}

Model& Scene::model(model_id id)
{
	return _modelRegister.at(id);
}

const Model& Scene::model(model_id id) const
{
	return _modelRegister.at(id);
}

void Scene::render(Renderer& renderer) const
{
	for (const auto& idModelPair : _modelRegister)
		idModelPair.second.render(renderer);
}

}
