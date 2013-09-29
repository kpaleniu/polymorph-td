#pragma once

#include "filesystem/FileException.hpp"

#include <io/IOStream.hpp>

#include <string>

namespace polymorph { namespace filesystem {

class FileOutputStream : public io::OutputStream
{
public:
	FileOutputStream(const std::string& path);
	~FileOutputStream();

	void write(const void* data,
			   std::size_t typeAlignment,
			   std::size_t size,
			   std::size_t count);

private:
	std::FILE* _fp;
};

} }