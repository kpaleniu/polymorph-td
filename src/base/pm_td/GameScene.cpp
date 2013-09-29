#include "pm_td/GameScene.hpp"

#include <sys/Systems.hpp>

#include <Debug.hpp>

namespace polymorph { namespace pm_td {

namespace 
{
	const char* TAG = "GameScene";
}

GameScene::GameScene(gr::MeshManager& meshes)
:	_grScene(),
	_meshes(meshes)
{
}

GameScene::GameScene(GameScene&& other)
:	_grScene(std::move(other._grScene)),
	_meshes(other._meshes)
{
}

void GameScene::addModel(model_id id, ModelType&& model)
{
	DEBUG_OUT(TAG, "Adding model %i", int(id));
	_grScene.addModel(id, std::move(model));
}

void GameScene::removeModel(model_id id)
{
	DEBUG_OUT(TAG, "Removing model %i", int(id));
	_grScene.removeModel(id);
}

GameScene::ModelType& GameScene::model(model_id id)
{
	return _grScene.model(id);
}

const GameScene::ModelType& GameScene::model(model_id id) const
{
	return _grScene.model(id);
}

GameScene::CameraType& GameScene::camera()
{
	return _grScene.camera();
}

const GameScene::CameraType& GameScene::camera() const
{
	return _grScene.camera();
}

gr::MeshManager::Handle GameScene::addMesh(mesh_id id, gr::Mesh&& mesh)
{
	DEBUG_OUT(TAG, "Adding mesh %i", int(id));
	return _meshes.add(id, std::move(mesh));
}

gr::MeshManager::Handle GameScene::getMesh(mesh_id id)
{
	return _meshes.get(id);
}

const gr::MeshManager::Handle GameScene::getMesh(mesh_id id) const
{
	return _meshes.get(id);
}

bool GameScene::hasMesh(mesh_id id) const
{
	return _meshes.has(id);
}

void GameScene::flush() const
{
	auto& grSys = sys::Systems::system<sys::GraphicsSystem>();
	auto sceneMutator = grSys.sceneMutator();

	sceneMutator.scene = _grScene;
}

} }