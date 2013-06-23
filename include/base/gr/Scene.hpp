#ifndef GR_SCENE_HPP
#define GR_SCENE_HPP

#include "gr/types.hpp"
#include "gr/Model.hpp"

#include <text/util.hpp>

#include <map>

namespace gr {

class Scene
{
public:
	typedef text::string_hash model_id;
	
	Scene();
	Scene(Scene&& other);
	
	void addModel(model_id id, Model&& model);
	void removeModel(model_id id);

	Model& model(model_id id);
	const Model& model(model_id id) const;
	
	void render(Renderer& renderer) const;



private:
	std::map<model_id, Model> _modelRegister;
};

}

#endif
