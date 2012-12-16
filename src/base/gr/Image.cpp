
#include "gr/Image.hpp"

namespace gr {

Image::Image(unsigned int w,
             unsigned int h,
             PixelFormat format,
             unsigned int rowAlignment,
             unsigned char* pixels)
:	_width(w),
 	_height(h),
 	_format(format),
 	_rowAlignment(rowAlignment),
 	_pixels(pixels)
{
}

Image::Image(Image&& image)
:	_width(image._width),
 	_height(image._height),
 	_format(image._format),
 	_rowAlignment(image._rowAlignment),
 	_pixels(image._pixels)
{
	image._pixels = nullptr;
}

Image::~Image()
{
	if (_pixels != nullptr)
		delete[] _pixels;
}

unsigned int Image::getWidth() const
{
	return _width;
}

unsigned int Image::getHeight() const
{
	return _height;
}

PixelFormat Image::getPixelFormat() const
{
	return _format;
}

unsigned int Image::getRowAlignment() const
{
	return _rowAlignment;
}

const unsigned char* Image::data() const
{
	return _pixels;
}

}
