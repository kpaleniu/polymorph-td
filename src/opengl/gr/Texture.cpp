#include "gr/Texture.hpp"
#include "gr/GraphicsException.hpp"

namespace gr {

Texture::Texture(const Image& source,
                 const TextureParams& texParams)
:	_texID(0)
{
	glGenTextures(1, &_texID);
	if (_texID == 0)
		throw GraphicsException("Can't create texture.");

	glPixelStorei(GL_UNPACK_ALIGNMENT, source.getRowAlignment());

	glBindTexture(GL_TEXTURE_2D, _texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLint(texParams.sWrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLint(texParams.tWrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GLint(texParams.magZoom));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GLint(texParams.minZoom));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	             source.getWidth(), source.getHeight(),
	             0, GLint(source.getPixelFormat()),
	             GL_UNSIGNED_BYTE, source.data());

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture&& other)
:	_texID(other._texID)
{
	other._texID = 0;
}

Texture::~Texture()
{
	if (_texID != 0)
		glDeleteTextures(1, &_texID);
}

Texture::BindLock Texture::bindLock()
{
	return BindLock([this]{ glBindTexture(GL_TEXTURE_2D, _texID); },
	                [this]{ glBindTexture(GL_TEXTURE_2D, 0); });
}

}
