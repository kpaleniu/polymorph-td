#include "filesystem/FileInputStream.hpp"

#include "filesystem/FileException.hpp"

namespace polymorph { namespace filesystem {

FileInputStream::FileInputStream(const std::string& path)
{
#ifdef _WIN32
	if (fopen_s(&_fp, path.c_str(), "rb") != 0)
		throw FileOpenException();
#else
	_fp = std::fopen(path.c_str(), "rb");
	if (!_fp)
		throw FileOpenException();
#endif

	std::fseek(_fp, 0L, SEEK_END);
	
	long temp = std::ftell(_fp);
	if (temp == -1L)
		throw FileOpenException();

	_fileSize = std::size_t(temp);

	std::fseek(_fp, 0L, SEEK_SET);
}

FileInputStream::~FileInputStream()
{
	std::fclose(_fp);
}

std::size_t FileInputStream::available() const
{
	long temp = std::ftell(_fp);
	if (temp == -1L)
		throw FileException();

	return _fileSize - temp;
}

void FileInputStream::setReadPosition(long offset)
{
	if (std::fseek(_fp, offset, SEEK_SET) != 0)
		throw FileException();
}

long FileInputStream::getReadPosition() const
{
	long rVal = ftell(_fp);

	if (rVal == -1L)
		throw FileException();

	return rVal;
}

void FileInputStream::read(void* data, std::size_t /*typeAlignment*/, std::size_t size, std::size_t count)
{
	if (std::fread(data, size, count, _fp) < count)
	{
		// WARNING: The data buffer may not be in a valid state after this.
		throw FileReadException();
	}
}

} }