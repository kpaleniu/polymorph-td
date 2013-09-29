#pragma once

#include "gr/DebugDraw.hpp"
#include "gr/RenderPassManager.hpp"
#include "gr/types.hpp"

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <functional>
#include <map>

namespace polymorph { namespace gr {

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

	void render(const MapMatrix4x4_r& projection,
				const MapMatrix4x4_r& worldInverseTransform);

	DebugDraw& debugDraw();
	RenderPassManager& renderPassManager();

private:
	Surface& _surface;

	DebugDraw			_debugDraw;
	RenderPassManager	_renderPassManager;
};

} }
