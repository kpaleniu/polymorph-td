
#ifndef FILESYSTEM_FILE_INPUT_STREAM_HPP_
#define FILESYSTEM_FILE_INPUT_STREAM_HPP_

#include <io/IOStream.hpp>

#include <string>
#include <cstdio>

namespace filesystem {

class FileInputStream : public io::InputStream
{
public:
	FileInputStream(const std::string& path);
	~FileInputStream();

	std::size_t available() const;

	void setReadPosition(long offset);
	long getReadPosition() const;

protected:
	void read(void* data, std::size_t typeAlignment, std::size_t size, std::size_t count);

private:
	std::FILE* _fp;
	std::size_t _fileSize;
};

}

#endif
