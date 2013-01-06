/**
 * @file VertexFormat.cpp
 *
 */

#include "gr/VertexFormat.hpp"

#include "Assert.hpp"

namespace gr {

namespace {

const VertexFormatData vertexFormatData[size_t(VertexFormat::VERTEX_ENUM_SIZE)] =
{
//
// S = sum
// V = vertex dim
// C = color dim
// T = texture coordinate dim
// N = normal (0 or 3)
//
//	  S  V  C  T  N  ARRAY FLAGS
	{ 2, 2, 0, 0, 0, format_flags(VertexFormatFlag::VERT_FLAG) },	// V2
	{ 5, 2, 3, 0, 0, format_flags(VertexFormatFlag::VERT_FLAG) |
					 format_flags(VertexFormatFlag::COLOR_FLAG) },	// V2_C3
	{ 6, 2, 4, 0, 0, format_flags(VertexFormatFlag::VERT_FLAG) |
					 format_flags(VertexFormatFlag::COLOR_FLAG) },	// V2_C4
	{ 4, 2, 0, 2, 0, format_flags(VertexFormatFlag::VERT_FLAG) |
					 format_flags(VertexFormatFlag::TEXT_FLAG) },	// V2_T2
	{ 7, 2, 3, 2, 0, format_flags(VertexFormatFlag::VERT_FLAG) |
					 format_flags(VertexFormatFlag::COLOR_FLAG) |
					 format_flags(VertexFormatFlag::TEXT_FLAG) },	// V2_C3_T2
	{ 8, 2, 4, 2, 0, format_flags(VertexFormatFlag::VERT_FLAG) |
					 format_flags(VertexFormatFlag::COLOR_FLAG) |
					 format_flags(VertexFormatFlag::TEXT_FLAG) } 	// V2_C4_T2
};

}

const VertexFormatData& getVertexFormatData(VertexFormat fmt)
{
	ASSERT(fmt != VertexFormat::VERTEX_ENUM_SIZE, "Bad vertex format.");
	return vertexFormatData[size_t(fmt)];
}

}
