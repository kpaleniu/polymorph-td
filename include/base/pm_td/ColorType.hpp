#pragma once

#include <gr/types.hpp>

#include <string>

namespace polymorph { namespace pm_td {

enum class ColorType : char
{
	RED = 0,
	GREEN,
	BLUE,
	WHITE
};

struct ColorTypeData
{
	gr::real_t color[3];
	std::string typeName;
};

const ColorTypeData& getColorTypeData(ColorType colorType);

} }