#pragma once

#include <io/IOException.hpp>

namespace polymorph { namespace filesystem {

PM_MAKE_EXCEPTION_CLASS(FileException, io::IOException);

PM_MAKE_EXCEPTION_CLASS(FileOpenException, FileException);

PM_MAKE_EXCEPTION_CLASS(FileWriteException, FileException);

PM_MAKE_EXCEPTION_CLASS(FileReadException, FileException);

} }