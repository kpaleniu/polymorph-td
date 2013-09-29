#pragma once

#include "filesystem/FileInputStream.hpp"
#include "filesystem/FileOutputStream.hpp"

#include <string>

namespace polymorph { namespace filesystem {

class FileSystem
{
public:
	static const std::string& dataFolder();
	
	static FileOutputStream createTempFile(const std::string& filename, bool allowOverwrite = true);
	static FileInputStream openTempFile(const std::string& filename);
	static void removeTempFiles();
};

} }