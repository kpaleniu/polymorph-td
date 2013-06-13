/**
 * @file RenderPassManager.hpp
 *
 */

#ifndef RENDERPASSMANAGER_HPP_
#define RENDERPASSMANAGER_HPP_

#include "gr/RenderPass.hpp"
#include "gr/TextureManager.hpp"

#include <NonCopyable.hpp>

#include <map>

namespace gr {

/**
 * Render pass composition.
 */
class RenderPassManager : NonCopyable
{
public:
	RenderPassManager();
	RenderPassManager(RenderPassManager&& other);

	void pushProjection(const Projection& projection);
	void popProjection();

	void pushTransform(const Transform& transform);
	void popTransform();

	VertexWriter& vertexWriter(VertexFormat format, 
							   Primitive shape,
							   TextureManager::TextureHandle tex, 
							   const Shader* shader);

	void render();
	void clear();

private:

	typedef unsigned int projection_index;
	typedef unsigned int transform_index;
	

	// To keep track of stack history a tree is needed.

	template <typename T>
	struct RandomAccessTreeEntry
	{
		static const unsigned int NULL_PARENT_INDEX = -1;

		unsigned int parentIndex;
		T data;
	};

	std::vector<RandomAccessTreeEntry<Projection>> _projectionPool;
	std::vector<RandomAccessTreeEntry<Transform>> _transformPool;

	projection_index _currentProjectionIndex;
	transform_index _currentTransformIndex;

	struct WorldState
	{
		projection_index projection;
		transform_index transformation;

		bool operator<(const WorldState& other) const
		{
			// Same operator< as for std::pair<unsigned int, unsigned int>.

			if (projection < other.projection)
				return true;
			
			if (projection > other.projection)
				return false;

			return transformation < other.transformation;
		}
	};


	// TODO Needs refactoring

	std::multimap<WorldState, RenderPass> _renderPasses;

};

}


#endif /* RENDERPASSMANAGER_HPP_ */
