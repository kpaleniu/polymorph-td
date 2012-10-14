#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "NonCopyable.hpp"
//#include "gr/TextureHandler.hpp"

namespace gr
{
	class Surface;

	class Renderer : NonCopyable
	{
	public:
		Renderer(Surface& surface);
		Renderer(Renderer&& renderer);
		~Renderer();

		void setClearColor(float r, float g, float b, float a=1.0f);

		void clearBuffers();

		void flipBuffers();

		// TextureHandler &textures();

	protected:

	private:
		//TextureHandler _texHandler;

		Surface& _surface;
	};
}

#endif
