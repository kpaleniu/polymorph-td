#pragma once

#include <gr/Scene.hpp>
#include <gr/MeshManager.hpp>

#include <map>
#include <vector>

namespace polymorph { namespace pm_td {

/**
 * Graphics scene, mesh manager and game-specific scene facade.
 */
class GameScene
{
public:
	typedef gr::Model<gr::Transform2> ModelType;
	typedef gr::Camera<gr::Transform2> CameraType;

	typedef gr::Scene<gr::Transform2>::model_id model_id;
	typedef gr::MeshManager::product_id mesh_id;

public:
	GameScene(gr::MeshManager& meshes);
	GameScene(GameScene&& other);

	// Scene access:
	void addModel(model_id id, ModelType&& model);
	void removeModel(model_id id);

	ModelType& model(model_id id);
	const ModelType& model(model_id id) const;

	CameraType& camera();
	const CameraType& camera() const;
	//

	// Mesh access:
	gr::MeshManager::Handle addMesh(mesh_id id, gr::Mesh&& mesh);

	gr::MeshManager::Handle getMesh(mesh_id id);
	const gr::MeshManager::Handle getMesh(mesh_id id) const;

	bool hasMesh(mesh_id id) const;
	//

	void flush() const;

private:
	gr::Scene<gr::Transform2> _grScene;
	gr::MeshManager& _meshes;

	GameScene& operator=(const GameScene& other);
};

} }