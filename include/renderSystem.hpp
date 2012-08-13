#ifndef POLYMORPH_RENDER_SYSTEM_HPP
#define POLYMORPH_RENDER_SYSTEM_HPP

#include <vector>
#include <boost/shared_ptr.hpp>

class RenderData {
public:
	typedef boost::shared_ptr<RenderData> ptr;

	virtual ~RenderData() {}
	virtual void render() = 0;
};

class RenderSystem {
	std::vector<RenderData::ptr> _renderList;
public:
	void renderAll();

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

#endif /* POLYMORPH_RENDER_SYSTEM_HPP */
