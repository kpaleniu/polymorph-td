#ifndef POLYMORPH_RENDER_SYSTEM_HPP
#define POLYMORPH_RENDER_SYSTEM_HPP

#include <vector>
#include "renderData.hpp"

namespace PolyMorph {

class RenderSystem {
	std::vector<RenderData::ptr> _renderList;
public:
	void renderAll()
	{
		for (std::vector<RenderData::ptr>::const_iterator iter
				= _renderList.begin();
			 iter != _renderList.end(); ++iter)
		{
			/* Note that *iter is a shared_ptr<AnimationData> */
			(*iter)->render();
		}
	}

	void addToRendering(RenderData::ptr const& data)
	{
		_renderList.push_back(data);
	}

	void removeFromRendering(RenderData::ptr& data)
	{
		_renderList.erase(
				std::remove(_renderList.begin(), _renderList.end(), data),
				_renderList.end()
		);
	}

	bool isRendering(RenderData::ptr const& data) const
	{
		std::vector<RenderData::ptr>::const_iterator it;
		it = std::find(_renderList.begin(), _renderList.end(), data);

		return it != _renderList.end() ? true : false;
	}
};

} /* namespace PolyMorph */

#endif /* POLYMORPH_RENDER_SYSTEM_HPP */
