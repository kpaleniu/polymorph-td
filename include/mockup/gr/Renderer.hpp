#ifndef RENDERER_HPP_
#define RENDERER_HPP_


namespace gr
{
	class Surface;

	/**
	 * Mockup of renderer.
	 */
	class Renderer
	{
	public:
		Renderer(Surface &surface)
		{
		}
		~Renderer()
		{
		}

		void setClearColor(float r, float g, float b, float a=1.0f)
		{
		}

		void clearBuffers()
		{
		}
	};
}

#endif
