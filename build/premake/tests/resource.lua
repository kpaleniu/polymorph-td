
project "ImageReaderTest"
	kind "WindowedApp"
	language "C++"
	
	files { sourcePath .. "libpng/resource/**.cpp",
			sourcePath .. "base/resource/**.cpp",
			sourcePath .. "test/resource/test_ImageReader_main.cpp",
			sourcePath .. "test/gr/TestWindow.cpp",
			
			includePath .. "libpng/resource/**.hpp",
			includePath .. "base/resource/**.hpp",
			includePath .. "test/gr/TestWindow.hpp" }
	
	includedirs { includePath .. "test" }
	
	links { "gr", "ext", "concurrency", "text" }