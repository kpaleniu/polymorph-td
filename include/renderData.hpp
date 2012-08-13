#ifndef POLYMORPH_RENDER_DATA_HPP
#define POLYMORPH_RENDER_DATA_HPP

#include <boost/shared_ptr.hpp>

namespace PolyMorph {

class RenderData {
public:
	typedef boost::shared_ptr<RenderData> ptr;

	virtual ~RenderData() {}
	virtual void render() = 0;
};

} /* namespace PolyMorph */

#endif /* POLYMORPH_RENDER_DATA_HPP */
