/**
 * @file TextureManager_GL.cpp
 *
 */

/**
 * @file GLTextureHandler.cpp
 *
 */

#include "gr/TextureHandler.hpp"

#include <gl/gl.h>

namespace gr {

TextureHandler::TextureHandler()
		//: _currentTexture(/*0*/)
{

}

TextureHandler::~TextureHandler()
{

}

void TextureHandler::bindTexture(const Texture &/*tex*/)
{
	//glBindTexture(GL_TEXTURE_2D, tex.texId);
}
void TextureHandler::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
