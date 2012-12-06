#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "gr/DebugDraw.hpp"
#include "gr/BufferManager.hpp"
#include "gr/RenderObject.hpp"

#include "PrivateHandle.hpp"
#include "NonCopyable.hpp"


#include <functional>
#include <map>

namespace gr {

class Surface;

class Renderer : NonCopyable
{
private:
	struct RenderVariant
	{
		RenderVariant(RenderObject&) {}
		// TODO Put here data of render object that is not material.
	};

	typedef std::multimap<Material, RenderVariant>::iterator render_variant_iterator;

public:
	class RenderObjectHandle : public PrivateHandle<render_variant_iterator>
	{
		RenderObjectHandle() : PrivateHandle<render_variant_iterator>() {}
		RenderObjectHandle(const render_variant_iterator& v) : PrivateHandle<render_variant_iterator>(v) {}

		friend class Renderer;
	};

	Renderer(Surface& surface);
	Renderer(Renderer&& renderer);
	~Renderer();

	void setClearColor(float r, float g, float b, float a=1.0f);

	void clearBuffers();

	void flipBuffers();

	void render();

	//RenderObjectHandle addRenderObject(RenderObject&& renderObject);
	void removeRenderObject(RenderObjectHandle handle);

	DebugDraw& debugDraw();
	BufferManager& bufferManager();

private:
	Surface& _surface;

	DebugDraw _debugDraw;
	BufferManager _bufferManager;

	std::multimap<Material, RenderVariant> _renderObjects;
};

}

#endif
