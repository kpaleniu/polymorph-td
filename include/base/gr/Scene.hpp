#pragma once

#include "gr/types.hpp"
#include "gr/Model.hpp"
#include "gr/Camera.hpp"

#include <map>

namespace polymorph { namespace gr {

template <typename TransformType = Transform3>
class Scene
{
public:
	typedef std::size_t model_id;
	
	Scene(const Camera<TransformType>& camera = Camera<TransformType>());
	Scene(Scene<TransformType>&& other);
	Scene(const Scene<TransformType>& other);

	void addModel(model_id id, Model<TransformType>&& model);
	void removeModel(model_id id);

	Model<TransformType>& model(model_id id);
	const Model<TransformType>& model(model_id id) const;

	const Camera<TransformType>& camera() const;
	Camera<TransformType>& camera();

	void render(Renderer& renderer) const;

	Scene<TransformType>& operator=(const Scene<TransformType>& other);

private:
	std::map<model_id, Model<TransformType>> _modelRegister;

	Camera<TransformType> _camera;
};

} }

#include "gr/Scene.inl"
