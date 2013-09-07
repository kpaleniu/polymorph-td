#ifndef GR_SCENE_HPP
#define GR_SCENE_HPP

#include "gr/types.hpp"
#include "gr/Model.hpp"

#include <text/util.hpp>

#include <map>

namespace gr {

template <typename TransformType = Transform3>
class Scene
{
public:
	typedef text::string_hash model_id;
	
	Scene();
	Scene(Scene&& other);
	
	void addModel(model_id id, Model<TransformType>&& model);
	void removeModel(model_id id);

	Model<TransformType>& model(model_id id);
	const Model<TransformType>& model(model_id id) const;
	
	void render(Renderer& renderer) const;


private:
	std::map<model_id, Model<TransformType>> _modelRegister;
};

}

#include "gr/Scene.inl"

#endif
