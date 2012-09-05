#ifndef RENDERER_HPP_
#define RENDERER_HPP_

//#include "gr/TextureHandler.hpp"

namespace gr
{
	class Surface;

	class Renderer
	{
	public:
		Renderer(Surface &surface);
		~Renderer();

		void setClearColor(float r, float g, float b, float a=1.0f);

		void clearBuffers();

		// TextureHandler &textures();

	protected:

	private:
		//TextureHandler _texHandler;

		Surface &_surface;
	};
}

#endif
