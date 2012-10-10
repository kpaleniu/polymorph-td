#ifndef TEXTURE_HANDLER_HPP_
#define TEXTURE_HANDLER_HPP_

#include "Scoped.hpp"


namespace gr {

class Texture;
class Image;
struct TextureParams;

class TextureHandler
{
public:
	typedef Scoped BindLock;

	TextureHandler();
	~TextureHandler();

	void bindTexture(const Texture &tex);
	void unbindTexture();

	BindLock bindLock(const Texture &tex)
	{
		return BindLock(
			[&] { bindTexture(tex); },
			[&] { unbindTexture();  });
	}

	Texture &createTexture(Image &source,
						   TextureParams params);
	void destroyTexture(Texture &tex);

public:

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
	Texture *_curTex;
};

}

#endif
