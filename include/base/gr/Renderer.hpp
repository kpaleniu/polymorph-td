#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "NonCopyable.hpp"

#include "gr/DebugDraw.hpp"
#include "gr/BufferManager.hpp"

#include <functional>
#include <list>

namespace gr {

class Surface;

class Renderer : NonCopyable
{
public:
	typedef std::function<bool (Renderer&)> RenderAction;

	Renderer(Surface& surface);
	Renderer(Renderer&& renderer);
	~Renderer();

	void setClearColor(float r, float g, float b, float a=1.0f);

	void clearBuffers();

	void flipBuffers();

	void render();

	void addRenderAction(RenderAction&& action);

	DebugDraw& debugDraw();
	BufferManager& bufferManager();

private:
	Surface& _surface;

	DebugDraw _debugDraw;
	BufferManager _bufferManager;

	std::list<RenderAction> _renderList;
};

}

#endif
