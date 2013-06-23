#ifndef GR_MESH_MANAGER_HPP_
#define GR_MESH_MANAGER_HPP_

#include "gr/Mesh.hpp"

#include <resource/ResourceLoader.hpp>

namespace gr {

class MeshManager : public resource::ResourceLoader<Mesh>
{
public:
	typedef resource::ResourceLoader<Mesh>::ResourceHandle MeshHandle;

	MeshManager();
	MeshManager(MeshManager&& other);

	MeshHandle addMesh(text::string_hash id, Mesh&& mesh);
	MeshHandle getMesh(text::string_hash id) const;

	static const MeshHandle NULL_MESH;
};

}


#endif