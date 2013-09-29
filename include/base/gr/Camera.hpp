#pragma once

#include "gr/types.hpp"


namespace polymorph { namespace gr {

template <typename TransformType>
struct Camera
{
	TransformType transform;
	Projection projection;
};


} }