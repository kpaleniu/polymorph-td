#pragma once

#include "gr/PixelFormat.hpp"
#include "gr/opengl.hpp"

#include <NonCopyable.hpp>

namespace polymorph { namespace gr {

class Image : NonCopyable
{
public:
	Image(unsigned int w,
	      unsigned int h,
	      PixelFormat format,
	      unsigned int rowAlignment,
	      unsigned char* pixels);

	Image(Image&& image);

	~Image();

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	PixelFormat getPixelFormat() const;
	unsigned int getRowAlignment() const;
	const unsigned char* data() const;

private:
	unsigned int _width;
	unsigned int _height;
	PixelFormat _format;
	unsigned int _rowAlignment;
	unsigned char* _pixels;
};

} }
