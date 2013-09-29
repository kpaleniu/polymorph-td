

#include "gr/Scene.hpp"

#include <Debug.hpp>

namespace polymorph { namespace gr {

template <typename TransformType>
Scene<TransformType>::Scene(const Camera<TransformType>& camera)
:	_modelRegister(),
	_camera(camera)
{
}

template <typename TransformType>
Scene<TransformType>::Scene(Scene<TransformType>&& other)
:	_modelRegister(std::move(other._modelRegister)),
	_camera(other._camera)
{
}

template <typename TransformType>
Scene<TransformType>::Scene(const Scene<TransformType>& other)
:	_modelRegister(other._modelRegister),
	_camera(other._camera)
{
}

template <typename TransformType>
void Scene<TransformType>::addModel(model_id id, Model<TransformType>&& model)
{
	ASSERT(_modelRegister.find(id) == _modelRegister.end(), "Trying to overwrite model in scene.");

	DEBUG_OUT("Scene", "Adding model %i", (int) id);

	_modelRegister.insert(std::make_pair(id, std::move(model)));
}

template <typename TransformType>
void Scene<TransformType>::removeModel(model_id id)
{
	ASSERT(_modelRegister.find(id) != _modelRegister.end(), "Trying to remove non-existing model.");

	DEBUG_OUT("Scene", "Removing model %i", (int) id);

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
const Camera<TransformType>& Scene<TransformType>::camera() const
{
	return _camera;
}

template <typename TransformType>
Camera<TransformType>& Scene<TransformType>::camera()
{
	return _camera;
}

template <typename TransformType>
void Scene<TransformType>::render(Renderer& renderer) const
{
	for (const auto& idModelPair : _modelRegister)
		idModelPair.second.render(renderer);
}

template <typename TransformType>
Scene<TransformType>& 
	Scene<TransformType>::operator=(const Scene<TransformType>& other)
{
	_modelRegister = other._modelRegister;
	_camera = other._camera;

	return *this;
}

} }