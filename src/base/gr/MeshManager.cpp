#include "gr/MeshManager.hpp"


namespace polymorph { namespace gr {

const MeshManager::MeshHandle MeshManager::NULL_MESH = MeshManager::MeshHandle();

MeshManager::MeshManager()
:	ResourceManager()
{
}

MeshManager::MeshManager(MeshManager&& other)
:	ResourceManager(std::forward<MeshManager>(other))
{
}

MeshManager::MeshHandle MeshManager::addMesh(text::string_hash id, Mesh&& mesh)
{
	return addProduct(id, std::move(mesh));
}

MeshManager::MeshHandle MeshManager::getMesh(text::string_hash id) const
{
	return getProduct(id);
}

bool MeshManager::hasMesh(text::string_hash id) const
{
	return hasProduct(id);
}


} }