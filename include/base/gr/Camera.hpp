#ifndef GR_CAMERA_HPP_
#define GR_CAMERA_HPP_

#include "gr/types.hpp"


namespace gr {

template <typename TransformType>
struct Camera
{
	TransformType transform;
	Projection projection;
};


}

#endif