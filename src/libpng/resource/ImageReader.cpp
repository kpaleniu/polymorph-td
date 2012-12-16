#include "resource/ImageReader.hpp"
#include "resource/ResourceException.hpp"

#include <gr/PixelFormat.hpp>

#include <cstdio>

#include <png.h>

namespace resource {

namespace {

constexpr unsigned int pngHeaderCheckSize = 8;

bool isPNGFile(FILE* fp)
{
	unsigned char header[pngHeaderCheckSize];
	fread(header, 1, pngHeaderCheckSize, fp);
	return !png_sig_cmp(header, 0, pngHeaderCheckSize);
}

}

ImageReader::ImageHandle ImageReader::getImage(text::string_hash id)
{
	if (hasProduct(id))
		return getProduct(id);

	// Image is not in cache, load it.

	const std::string& url = text::get(id);

	FILE* fp = fopen(url.c_str(), "rb");

	if (fp == NULL)
		throw ResourceException("Cannot open file.");

	if ( !isPNGFile(fp) )
	{
		fclose(fp);
		throw ResourceException("File is not PNG.");
	}

	png_structp pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!pngStruct)
	{
		fclose(fp);
		throw ResourceException("[LIBPNG] Error creating read struct.");
	}

	png_infop pngInfo = png_create_info_struct(pngStruct);
	if (!pngInfo)
	{
		png_destroy_read_struct(&pngStruct, nullptr, nullptr);
		fclose(fp);
		throw ResourceException("[LIBPNG] Error creating info struct.");
	}

	if ( setjmp(png_jmpbuf(pngStruct)) )
	{
		png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);
		fclose(fp);
		throw ResourceException("Error while reading file.");
	}

	png_init_io(pngStruct, fp);

	png_set_sig_bytes(pngStruct, pngHeaderCheckSize);

	// FIXME Write directly to buffer, don't copy.

	png_read_png(pngStruct,
	             pngInfo,
	             PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND,
	             NULL);

	struct
	{
		png_uint_32 width;
		png_uint_32 height;
		png_byte bitsPerPixel;
		png_byte colorType;
		png_size_t rowSize;
	} imageData;

	imageData.width 		= png_get_image_width(pngStruct, pngInfo);
	imageData.height 		= png_get_image_height(pngStruct, pngInfo);
	imageData.bitsPerPixel 	= png_get_bit_depth(pngStruct, pngInfo);
	imageData.colorType 	= png_get_color_type(pngStruct, pngInfo);
	imageData.rowSize		= png_get_rowbytes(pngStruct, pngInfo);

	// FIXME Let PixelFormat decide what format is suitable.

	gr::PixelFormat fmt;
	if (imageData.colorType == PNG_COLOR_TYPE_RGBA)
		fmt = gr::PixelFormat::R8G8B8A8;
	else
		fmt = gr::PixelFormat::R8G8B8;

	unsigned char* pixels = new unsigned char[imageData.rowSize * imageData.height];
	png_bytepp rowPointers = png_get_rows(pngStruct, pngInfo);

	for (unsigned int i = 0; i < imageData.height; i++)
		memcpy(pixels + (imageData.rowSize * (imageData.height - 1 - i)),
		       rowPointers[i],
		       imageData.rowSize);

	png_destroy_read_struct(&pngStruct, &pngInfo, NULL);
	fclose(fp);

	return addProduct(id, gr::Image((unsigned int) imageData.width,
	                                (unsigned int) imageData.height,
	                                fmt,
	                                1u,
	                                pixels));
}


}

