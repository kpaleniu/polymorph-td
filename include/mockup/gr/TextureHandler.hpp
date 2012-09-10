#ifndef TEXTURE_HANDLER_HPP_
#define TEXTURE_HANDLER_HPP_

namespace gr {

class Texture;
class Image;
struct TextureParams;

class TextureHandler
{
public:
	class BindLock;

	TextureHandler()
	{
	}
	~TextureHandler()
	{
	}

	void bindTexture(const Texture &tex)
	{
	}
	void unbindTexture()
	{
	}
	BindLock bindLock(const Texture &tex)
	{
	}

	Texture &createTexture(Image &source,
						   TextureParams params)
	{
	}
	void destroyTexture(Texture &tex)
	{
	}

public:
	class BindLock
	{
	private:
		friend class TextureHandler;

		BindLock(TextureHandler &handler,
				 const Texture &tex)
		{
		}

		~BindLock()
		{
		}
	};

	struct TextureParams
	{
		enum Wrap
		{
			CLAMP, REPEAT, WRAP_SIZE
		} sWrap, rWrap;

		enum Zoom
		{
			NEAREST, LINEAR, ZOOM_SIZE
		} minZoom, magZoom;
	};

private:
};

}

#endif
