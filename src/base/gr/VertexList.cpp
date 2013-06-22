#include "gr/VertexList.hpp"

#include <Assert.hpp>

namespace gr {

VertexList::VertexList(VertexFormat format_,
					   std::vector<real_t>&& vertices_,
					   std::vector<real_t>&& colors_,
					   std::vector<real_t>&& texCoords_)
:	format(format_),
	vertices(std::move(vertices_)),
	colors(std::move(colors_)),
	texCoords(std::move(texCoords_))
{
#ifdef _DEBUG

	auto fmtData = getVertexFormatData(format);

	ASSERT( (vertices.size() % fmtData.vertDim) == 0, "Bad vertex input to VertexList" );
	
	unsigned int count = vertices.size() / fmtData.vertDim;

	ASSERT(colors.size() == fmtData.colorDim * count, "Bad color input to VertexList");
	ASSERT(texCoords.size() == fmtData.textDim * count, "Bad color input to VertexList");

#endif
}

VertexList::VertexList(VertexList&& other)
:	format(other.format),
	vertices(std::move(other.vertices)),
	colors(std::move(other.colors)),
	texCoords(std::move(other.texCoords))
{
}

real_t* VertexList::vertexData(index_t vertIndex)
{
	const auto& fmtData = getVertexFormatData(format);

	ASSERT(fmtData.vertDim * vertIndex < vertices.size(),
		   "VertexList vertices out of bounds");
	return vertices.data() + (fmtData.vertDim * vertIndex);
}

real_t* VertexList::colorData(index_t vertIndex)
{
	const auto& fmtData = getVertexFormatData(format);

	if (fmtData.colorDim == 0)
		return nullptr;

	ASSERT(fmtData.colorDim * vertIndex < colors.size(),
		   "VertexList vertices out of bounds");
	return colors.data() + (fmtData.colorDim * vertIndex);
}

real_t* VertexList::texCoordData(index_t vertIndex)
{
	const auto& fmtData = getVertexFormatData(format);

	if (fmtData.textDim == 0)
		return nullptr;

	ASSERT(fmtData.textDim * vertIndex < texCoords.size(),
		   "VertexList vertices out of bounds");
	return texCoords.data() + (fmtData.textDim * vertIndex);
}

const real_t* VertexList::vertexData(index_t vertIndex) const
{
	const auto& fmtData = getVertexFormatData(format);

	ASSERT(fmtData.vertDim * vertIndex < vertices.size(),
		   "VertexList vertices out of bounds");
	return vertices.data() + (fmtData.vertDim * vertIndex);
}

const real_t* VertexList::colorData(index_t vertIndex) const
{
	const auto& fmtData = getVertexFormatData(format);

	if (fmtData.colorDim == 0) 
		return nullptr;

	ASSERT(fmtData.colorDim * vertIndex < colors.size(),
		   "VertexList vertices out of bounds");
	return colors.data() + (fmtData.colorDim * vertIndex);
}

const real_t* VertexList::texCoordData(index_t vertIndex) const
{
	const auto& fmtData = getVertexFormatData(format);

	if (fmtData.textDim == 0)
		return nullptr;

	ASSERT(fmtData.textDim * vertIndex < texCoords.size(),
		   "VertexList vertices out of bounds");
	return texCoords.data() + (fmtData.textDim * vertIndex);
}

std::size_t VertexList::vertexCount() const
{
	const auto& fmtData = getVertexFormatData(format);

	ASSERT(vertices.size() % fmtData.vertDim == 0, "VertexList is ill-formed.");

	return vertices.size() / fmtData.vertDim;
}

}