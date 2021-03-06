#include "gr/Texture.hpp"
#include "gr/GraphicsException.hpp"

#include <Assert.hpp>

namespace polymorph { namespace gr {

Texture::Texture(const Image& source,
                 const Params& texParams)
:	_texID(0)
{
	glGenTextures(1, &_texID);
	if (_texID == 0)
		throw GraphicsException();

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

Texture::BindLock Texture::bindLock() const
{
	return BindLock([this]{ bind(); },
	                [this]{ unbind(); });
}

void Texture::bind() const
{
	ASSERT(_texID != 0, "Trying to bind invalid texture.");
	glBindTexture(GL_TEXTURE_2D, _texID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

} }