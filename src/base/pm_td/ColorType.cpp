#include "pm_td/ColorType.hpp"

namespace polymorph { namespace pm_td {

namespace
{
	const ColorTypeData data[] =
	{
		{ {1.0f, 0.0f, 0.0f}, "RED" },
		{ {0.0f, 1.0f, 0.0f}, "GREEN" },
		{ {0.0f, 0.0f, 1.0f}, "BLUE" },
		{ {1.0f, 1.0f, 1.0f}, "WHITE" }
	};
}


const ColorTypeData& getColorTypeData(ColorType colorType)
{
	return data[int(colorType)];
}

} }