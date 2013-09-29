#pragma once

#include <io/IOStream.hpp>

#include <string>
#include <cstdio>

namespace polymorph { namespace filesystem {

class FileInputStream : public io::InputStream
{
public:
	FileInputStream(const std::string& path);
	~FileInputStream();

	std::size_t available() const;

	void setReadPosition(long offset);
	long getReadPosition() const;

	void read(void* data, std::size_t typeAlignment, std::size_t size, std::size_t count);

private:
	std::FILE* _fp;
	std::size_t _fileSize;
};

} }