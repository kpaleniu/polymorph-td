#pragma once

#include "gr/opengl.hpp"
#include "gr/Image.hpp"

#include <Scoped.hpp>
#include <NonCopyable.hpp>

namespace polymorph { namespace gr {

class Texture : NonCopyable
{
public:
	typedef Scoped BindLock;

	struct Params
	{
		enum Wrap : GLint
		{
			CLAMP			= GL_CLAMP,
			CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
			REPEAT			= GL_REPEAT,
		} sWrap, tWrap;

		enum Zoom : GLint
		{
			NEAREST	= GL_NEAREST,
			LINEAR	= GL_LINEAR,
		} minZoom, magZoom;

		Params(Wrap _sWrap, Wrap _tWrap,
			   Zoom _minZoom, Zoom _magZoom)
		:	sWrap(_sWrap),
			tWrap(_tWrap),
			minZoom(_minZoom),
			magZoom(_magZoom)
		{
		}
	};

public:
	Texture(const Image& source, const Params& texParams);
	Texture(Texture&& other);
	~Texture();

	BindLock bindLock() const;

	void bind() const;
	void unbind() const;

private:
	GLuint _texID;
};

} }
