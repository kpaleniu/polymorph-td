#include "gr/MeshIO.hpp"

#include "gr/Mesh.hpp"
#include "gr/TextureManager.hpp"

#include <io/IOStream.hpp>

#include <Endianess.hpp>

#include <cstdint>

/*

File format of mesh:

-- HEADER --
unsigned char							version
uint32 (VertexFormat)					format
uint32 (Primitive)						shape
uint64									vertexCount
uint64									subMeshCount

--  DATA  --
float32[vertexCount * format.vertDim]	vertices
float32[vertexCount * format.colorDim]	colors
float32[vertexCount * format.textDim]	textureCoords

{
	uint64 (text::string_hash)	textureId
	uint64						indexCount
	uint64[indexCount]			indices
}[subMeshCount]							subMeshes

------------

*/


#define MESH_FILE_VERSION static_cast<unsigned char>(1)

namespace gr {


void MeshIO::writeMesh(io::OutputStream& ostream,
					   const Mesh& mesh,
					   bool outputBigEndian)
{
	if (isBigEndian() == outputBigEndian)
	{
		// HEADER

		ostream << MESH_FILE_VERSION;
		ostream << static_cast<std::uint32_t>(mesh._vertexList.format);
		ostream << static_cast<std::uint32_t>(mesh._shape);
		ostream << static_cast<std::uint64_t>(mesh._vertexList.vertexCount());
		ostream << static_cast<std::uint64_t>(mesh._subMeshes.size());

	
		// DATA

		for (float v : mesh._vertexList.vertices)
			ostream << v;

		for (float c : mesh._vertexList.colors)
			ostream << c;

		for (float t : mesh._vertexList.texCoords)
			ostream << t;

		for (const auto& subMesh : mesh._subMeshes)
		{
			ostream << static_cast<std::uint64_t>(subMesh._texHandle.id());
			ostream << static_cast<std::uint64_t>(subMesh._indices.size());

			for (std::uint64_t index : subMesh._indices)
				ostream << index;
		}
	}
	else
	{
		// HEADER

		ostream << MESH_FILE_VERSION;
		ostream << flippedEndianess(static_cast<std::int32_t>(mesh._vertexList.format));
		ostream << flippedEndianess(static_cast<std::uint64_t>(mesh._vertexList.vertexCount()));
		ostream << flippedEndianess(static_cast<std::uint64_t>(mesh._subMeshes.size()));

	
		// DATA

		for (float v : mesh._vertexList.vertices)
			ostream << flippedEndianess(v);

		for (float c : mesh._vertexList.colors)
			ostream << flippedEndianess(c);

		for (float t : mesh._vertexList.texCoords)
			ostream << flippedEndianess(t);

		for (const auto& subMesh : mesh._subMeshes)
		{
			ostream << flippedEndianess(static_cast<std::uint64_t>(subMesh._texHandle.id()));
			ostream << flippedEndianess(static_cast<std::uint64_t>(subMesh._indices.size()));

			for (std::uint64_t index : subMesh._indices)
				ostream << flippedEndianess(index);
		}
	}
}


Mesh MeshIO::readMesh(io::InputStream& istream, const TextureManager& textureManager, bool inputBigEndian)
{
	bool needEndianFlip = (inputBigEndian != isBigEndian());

	// HEADER

	{
		unsigned char version;
		istream >> version;

		if (version != MESH_FILE_VERSION)
			throw MeshFileFormatException();
	}


	VertexFormat format;

	{
		std::uint32_t format32u;
		istream >> format32u;

		if (needEndianFlip)
			flipEndianess(format32u);

		if (format32u >= static_cast<std::uint32_t>(VertexFormat::VERTEX_ENUM_SIZE))
			throw MeshFileFormatException();

		format = static_cast<VertexFormat>(format32u);
	}

	const auto& formatData = getVertexFormatData(format);


	Primitive shape;

	{
		std::uint32_t shape32u;
		istream >> shape32u;

		if (needEndianFlip)
			flipEndianess(shape32u);

		if (shape32u >= static_cast<std::uint32_t>(Primitive::PRIMITIVE_ENUM_SIZE))
			throw MeshFileFormatException();

		shape = static_cast<Primitive>(shape32u);
	}


	std::size_t vertexCount;

	{
		std::uint64_t vertexCount64u;
		istream >> vertexCount64u;

		if (needEndianFlip)
			flipEndianess(vertexCount64u);

		vertexCount = static_cast<std::size_t>(vertexCount64u);
	}


	std::size_t subMeshCount;

	{
		std::uint64_t subMeshCount64u;
		istream >> subMeshCount64u;

		if (needEndianFlip)
			flipEndianess(subMeshCount64u);

		subMeshCount = static_cast<std::size_t>(subMeshCount64u);
	}


	// DATA

	std::vector<real_t> vertices;
	
	for (std::size_t i = 0; i < vertexCount * formatData.vertDim; ++i)
	{
		float f;
		istream >> f;

		if (needEndianFlip)
			flipEndianess(f);

		vertices.push_back(static_cast<real_t>(f));
	}


	std::vector<real_t> colors;

	for (std::size_t i = 0; i < vertexCount * formatData.colorDim; ++i)
	{
		float c;
		istream >> c;

		if (needEndianFlip)
			flipEndianess(c);

		colors.push_back(static_cast<real_t>(c));
	}


	std::vector<real_t> texCoords;

	for (std::size_t i = 0; i < vertexCount * formatData.textDim; ++i)
	{
		float t;
		istream >> t;

		if (needEndianFlip)
			flipEndianess(t);

		texCoords.push_back(static_cast<real_t>(t));
	}

	Mesh rMesh(VertexList(format, std::move(vertices), std::move(colors), std::move(texCoords)), shape);

	for (std::size_t i = 0; i < subMeshCount; ++i)
	{
		text::string_hash texId;

		{
			std::uint64_t texId64u;
			istream >> texId64u;

			if (needEndianFlip)
				flipEndianess(texId64u);

			texId = static_cast<text::string_hash>(texId64u);
		}


		std::size_t indexCount;

		{
			std::uint64_t indexCount64u;
			istream >> indexCount64u;

			if (needEndianFlip)
				flipEndianess(indexCount64u);

			indexCount = static_cast<std::size_t>(indexCount64u);
		}


		std::vector<index_t> indices;

		for (std::size_t j = 0; j < indexCount; ++j)
		{
			index_t index;

			{
				std::uint64_t index64u;
				istream >> index64u;

				if (needEndianFlip)
					flipEndianess(index64u);

				index = static_cast<index_t>(index64u);
			}

			indices.push_back(index);
		}

		rMesh.addSubMesh(textureManager.getTexture(texId), std::move(indices));
	}

	return rMesh;
}


}