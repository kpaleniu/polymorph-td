
#ifndef FILESYSTEM_FILESYSTEM_HPP_
#define FILESYSTEM_FILESYSTEM_HPP_

#include "filesystem/FileInputStream.hpp"
#include "filesystem/FileOutputStream.hpp"

#include <string>

namespace filesystem {

class FileSystem
{
public:
	static const std::string& dataFolder();
	
	static FileOutputStream createTempFile(const std::string& filename, bool allowOverwrite = true);
	static FileInputStream openTempFile(const std::string& filename);
	static void removeTempFiles();
};

}

#endif /* ANY_HPP_ */
