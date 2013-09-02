


#ifndef GR_ENTITY_HPP
#define GR_ENTITY_HPP

#include "gr/types.hpp"
#include "gr/TextureManager.hpp"
#include "gr/VertexWriter.hpp"
#include "gr/VertexFormat.hpp"

#include <vector>
#include <functional>

namespace gr {
/*
class ModelRegister
{
public:
	typedef text::string_hash model_key;

	void moveToRegister(Model&& model);
	Model&& removeFromRegister(model_key key);

	const Model& findModel(model_key key) const;
	bool hasModel(model_key key) const;

private:
	std::map<model_key, Model> _models;
};
*/

struct Model
{
	std::vector<real_t>  data;
	std::vector<index_t> indices;

	VertexFormat dataFmt;

	TextureManager::TextureHandle textureHandle;
};

struct Entity
{
	Transform transform;
	Model model;
	std::function<void (Entity&)> updater;

	void writeData(VertexWriter& writer) const;
};



}

#endif
