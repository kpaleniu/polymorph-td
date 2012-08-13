#ifndef POLYMORPH_RENDER_DATA_HPP
#define POLYMORPH_RENDER_DATA_HPP

#include <boost/shared_ptr.hpp>

namespace PolyMorph {

class AnimationData
{
public:
	typedef boost::shared_ptr<AnimationData> ptr;

	virtual ~AnimationData() {}
	virtual void animate() = 0;
};

} /* namespace PolyMorph */

#endif /* POLYMORPH_RENDER_DATA_HPP */
