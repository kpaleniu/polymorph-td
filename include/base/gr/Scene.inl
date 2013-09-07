

#include "gr/Scene.hpp"

#include <Debug.hpp>

namespace gr {

template <typename TransformType>
Scene<TransformType>::Scene()
:	_modelRegister()
{
}

template <typename TransformType>
Scene<TransformType>::Scene(Scene<TransformType>&& other)
	: _modelRegister(std::move(other._modelRegister))
{
}

template <typename TransformType>
void Scene<TransformType>::addModel(model_id id, Model<TransformType>&& model)
{
	ASSERT(_modelRegister.find(id) == _modelRegister.end(), "Trying to overwrite model in scene.");

	_modelRegister.insert(std::make_pair(id, std::move(model)));
}

template <typename TransformType>
void Scene<TransformType>::removeModel(model_id id)
{
	ASSERT(_modelRegister.find(id) != _modelRegister.end(), "Trying to remove non-existing model.");

	_modelRegister.erase(id);
}

template <typename TransformType>
Model<TransformType>& Scene<TransformType>::model(model_id id)
{
	return _modelRegister.at(id);
}

template <typename TransformType>
const Model<TransformType>& Scene<TransformType>::model(model_id id) const
{
	return _modelRegister.at(id);
}

template <typename TransformType>
void Scene<TransformType>::render(Renderer& renderer) const
{
	for (const auto& idModelPair : _modelRegister)
		idModelPair.second.render(renderer);
}

}