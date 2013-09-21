#ifndef GR_MESH_HPP_
#define GR_MESH_HPP_

#include "gr/VertexList.hpp"
#include "gr/TextureManager.hpp"
#include "gr/types.hpp"
#include "gr/MeshIO.hpp"
#include "gr/Renderer.hpp"

#include <NonCopyable.hpp>

#include <vector>

namespace gr {


class Mesh : NonCopyable
{
public:
	friend class MeshIO;

	class SubMesh : NonCopyable
	{
	public:
		friend class MeshIO;
		friend class Mesh;

		SubMesh(Mesh& parent,
				TextureManager::TextureHandle texHandle,
				std::vector<index_t>&& indices);

		// Note, should only be used when parent doesn't change.
		SubMesh(SubMesh&& other);
		
		void render(Renderer& renderer, 
					index_t meshStart) const;

	private:
		Mesh& _parent;

		TextureManager::TextureHandle _texHandle;

		std::vector<index_t> _indices;
	};

	Mesh(VertexList&& vertices, Primitive shape);

	Mesh(Mesh&& other);

	/* TODO If needed
	typedef std::vector<SubMesh>::iterator sub_mesh_it;

	sub_mesh_it begin();
	sub_mesh_it end();

	const sub_mesh_it begin() const;
	const sub_mesh_it end() const;
	*/

	void addSubMesh(TextureManager::TextureHandle texture,
					std::vector<index_t>&& indices);

	void render(Renderer& renderer) const;

	void render(Renderer& renderer, const Transform3& modelTransform) const;
	void render(Renderer& renderer, const Transform2& modelTransform) const;

	const VertexList& vertices() const;

private:
	VertexList _vertexList;
	std::vector<SubMesh> _subMeshes;

	Primitive _shape;
};


}

#endif