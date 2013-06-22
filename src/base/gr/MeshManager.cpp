#include "gr/MeshManager.hpp"


namespace gr {


const MeshManager::MeshHandle MeshManager::NULL_MESH = MeshManager::MeshHandle();

MeshManager::MeshHandle MeshManager::addMesh(text::string_hash id, Mesh&& mesh)
{
	return addProduct(id, std::move(mesh));
}

MeshManager::MeshHandle MeshManager::getMesh(text::string_hash id) const
{
	return getProduct(id);
}


}