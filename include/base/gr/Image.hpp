/**
 * @file VertexList.hpp
 *
 */

#ifndef VERTEXBUFFER_HPP_
#define IMAGE_HPP_

#include "gr/PixelFormat.hpp"
#include "gr/opengl.hpp"

#include <NonCopyable.hpp>

namespace gr {

class Image : NonCopyable
{
public:
	Image(unsigned int w,
	      unsigned int h,
	      PixelFormat format,
	      unsigned int rowAlignment,
	      const void* pixels);

	Image(Image&& image);


};

}


#endif /* IMAGE_HPP_ */
