
#include "gr/Entity.hpp"

#include <math/Matrix.hpp>

#include <Assert.hpp>

namespace gr {

// Vertices are saved as [v1, ..., vN, c1, ..., cN, t1, ..., tN, n1, ..., nN]
//  v - vertex
//  c - color
//  t - texture coordinate
//  n - normal

void Entity::writeData(VertexWriter& writer) const
{
	/*
	const auto& fmtData = getVertexFormatData(model.dataFmt);
	auto size = model.data.size();
	auto index = writer.getVertexCount();
	size_t pos = 0;
	size_t vertexCount = size / fmtData.size;

	ASSERT(size % fmtData == 0, "Bad vertex list format");

	if (model.dataFmt & VertexFormatFlag::VERT_FLAG)
	{
		for (int i = 0; i < vertexCount; ++i)
		{
			switch (fmtData.vertDim)
			{
				case 2:
				{
					math::MapVector2_r v(&model.data.data()[pos]);
					writer.vertices().write( (transform * v).data(), 2 );
					pos += 2;
					break;
				}
				case 3:
				{
					math::MapVector3_r v(&model.data.data()[pos]);
					writer.vertices().write( (transform * v).data(), 3 );
					pos += 3;
					break;
				}
				default:
				{
					ASSERT(false, "Bad vertex dimension");
					break;
				}
			}
		}
	}

	if (model.dataFmt & VertexFormatFlag::COLOR_FLAG)
	{
		writer.colors().write(&data.data()[pos], vertexCount * fmtData.colorDim);
		pos += vertexCount * fmtData.colorDim;
	}

	if (model.dataFmt & VertexFormatFlag::TEXT_FLAG)
	{
		writer.texCoords().write(&data.data()[pos], vertexCount * fmtData.textDim);
		pos += vertexCount * fmtData.textDim;
	}

	if (model.dataFmt & VertexFormatFlag::NORMAL_FLAG)
	{
		writer.texCoords().write(&data.data()[pos], vertexCount * fmtData.normalDim);
		pos += vertexCount * fmtData.normalDim;
	}
	*/
}

}

