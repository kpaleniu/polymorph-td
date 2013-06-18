#include "filesystem/FileOutputStream.hpp"


namespace filesystem {


FileOutputStream::FileOutputStream(const std::string& path)
{
#ifdef _WIN32
	if (fopen_s(&_fp, path.c_str(), "wb") != 0)
		throw FileOpenException();
#else
	_fp = std::fopen(path.c_str(), "wb");
	if (!_fp)
		throw FileOpenException();
#endif
}

FileOutputStream::~FileOutputStream()
{
	std::fclose(_fp);
}

void FileOutputStream::write(const void* data,
							 std::size_t /*typeAlignment*/,
							 std::size_t size,
							 std::size_t count)
{
	if (fwrite(data, size, count, _fp) < count)
	{
		// WARNING: The data buffer may not be in a valid state after this.
		throw FileWriteException();
	}
}



}