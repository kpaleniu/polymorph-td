#pragma once

#include <cstring>

namespace polymorph { namespace gr {

enum class VertexFormat : size_t
{
	V2 = 0,
	V2_C3,
	V2_C4,
	V2_T2,
	V2_C3_T2,
	V2_C4_T2,

	VERTEX_ENUM_SIZE
};

typedef unsigned char format_flags;

enum class VertexFormatFlag : format_flags
{
	VERT_FLAG   = 1,
	COLOR_FLAG  = (1<<1),
	TEXT_FLAG   = (1<<2),
	NORMAL_FLAG = (1<<3),
};

format_flags operator&(format_flags flags, VertexFormatFlag flag);
format_flags operator&(VertexFormatFlag flag, format_flags flags);
format_flags operator&(VertexFormatFlag flag1, VertexFormatFlag flag2);

format_flags operator|(format_flags flags, VertexFormatFlag flag);
format_flags operator|(VertexFormatFlag flag, format_flags flags);
format_flags operator|(VertexFormatFlag flag1, VertexFormatFlag flag2);

struct VertexFormatData
{
	std::size_t size;
	unsigned char vertDim;
	unsigned char colorDim;
	unsigned char textDim;
	unsigned char normalDim;
	format_flags fmtFlags;
};

const VertexFormatData& getVertexFormatData(VertexFormat fmt);

} }