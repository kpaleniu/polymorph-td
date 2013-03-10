#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "gr/DebugDraw.hpp"
#include "gr/BufferManager.hpp"
#include "gr/RenderPassManager.hpp"

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <functional>
#include <map>

namespace gr {

class Surface;

class Renderer : NonCopyable
{
public:


	typedef std::function<void ()> Hook;

	Renderer(Surface& surface);
	Renderer(Renderer&& renderer);
	~Renderer();

	void setClearColor(float r, float g, float b, float a=1.0f);

	void flipBuffers();

	void render();

	DebugDraw& debugDraw();

	RenderPassManager& renderPassManager();

private:
	Surface& _surface;

	DebugDraw _debugDraw;
	RenderPassManager _renderPassManager;
};

}

#endif
