/**
 * @file Transform2D.cpp
 *
 */

#include "math/Transform2D.hpp"


namespace math {

TransUST2D::TransUST2D(real scaling_, real translation_)
:	scaling(scaling_),
 	translation(translation_)
{
}

TransUST2D TransUST2D::operator*(const TransUST2D& trans) const
{
	return TransUST2D(scaling * trans.scaling,
	                  translation * trans.scaling + trans.translation);
}

}

