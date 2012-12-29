/**
 * @file Texture.hpp
 *
 */

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "gr/opengl.hpp"
#include "gr/Image.hpp"

#include <Scoped.hpp>
#include <NonCopyable.hpp>

namespace gr {

class Texture : NonCopyable
{
public:
	typedef Scoped BindLock;

	struct TextureParams
	{
		enum Wrap : GLint
		{
			CLAMP = GL_CLAMP,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			REPEAT = GL_REPEAT,
		} sWrap, tWrap;

		enum Zoom : GLint
		{
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
		} minZoom, magZoom;
	};

public:
	Texture(const Image& source, const TextureParams& texParams);
	Texture(Texture&& other);
	~Texture();

	BindLock bindLock() const;

private:
	GLuint _texID;
};

}

#endif /* TEXTURE_HPP_ */
