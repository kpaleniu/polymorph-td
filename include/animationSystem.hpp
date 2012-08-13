#ifndef POLYMORPH_ANIMATION_SYSTEM_HPP
#define POLYMORPH_ANIMATION_SYSTEM_HPP

#include <vector>
#include "animationData.hpp"

namespace PolyMorph {

class AnimationSystem
{
	std::vector<AnimationData::ptr_type> _animationList;
public:
	void animateAll()
	{
		for (std::vector<AnimationData::ptr_type>::const_iterator iter
				= _animationList.begin();
			 iter != _animationList.end(); ++iter)
		{
			/* Note that *iter is a shared_ptr<AnimationData> */
			(*iter)->animate();
		}
	}

	void addToAnimating(AnimationData::ptr_type const& data)
	{
		_animationList.push_back(data);
	}

	void removeFromAnimating(AnimationData::ptr_type& data)
	{
		_animationList.erase(
				std::remove(_animationList.begin(), _animationList.end(), data),
				_animationList.end()
		);
	}

	bool isAnimating(AnimationData::ptr_type const& data) const
	{
		std::vector<AnimationData::ptr_type>::const_iterator it;
		it = std::find(_animationList.begin(), _animationList.end(), data);

		return it != _animationList.end() ? true : false;
	}
};

} /* namespace PolyMorph */

#endif /* POLYMORPH_ANIMATION_SYSTEM_HPP */
