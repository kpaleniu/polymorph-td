#ifndef IMAGE_READER_HPP
#define IMAGE_READER_HPP

#include "resource/ResourceLoader.hpp"

#include <gr/Image.hpp>

namespace resource {

class ImageReader : public ResourceLoader<gr::Image>
{
public:
	typedef ResourceLoader<gr::Image>::ResourceHandle ImageHandle;

	ImageHandle getImage(text::string_hash id);
};

}



#endif
