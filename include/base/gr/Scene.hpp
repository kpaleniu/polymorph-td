


#ifndef GR_SCENE_HPP
#define GR_SCENE_HPP

#include "gr/types.hpp"
#include "gr/Model.hpp"

#include <text/util.hpp>

#include <NonCopyable.hpp>

#include <map>

namespace gr {

class Scene : NonCopyable
{
public:
	typedef text::string_hash model_id;

	Scene(){}
	
	Scene(Scene&& other)
	:	_models(std::move(other._models)) {}
	
	void addModel(model_id id, Model&& model)
	{
		_models.insert(std::make_pair(id, std::move(model)));
	}

	Model& model(model_id id)
	{
		return _models.at(id);
	}
	
	void render(Renderer& renderer) const
	{
		for (const auto& idModelPair : _models)
			idModelPair.second.render(renderer);
	}
	
	Scene& operator=(const Scene& other)
	{
		_models.clear();

		for (const auto& idModelPair : other._models)
			_models.insert(std::make_pair(idModelPair.first, idModelPair.second.cloneModelType()));

		return *this;
	}

private:
	std::map<model_id, Model> _models;
};

}

#endif
