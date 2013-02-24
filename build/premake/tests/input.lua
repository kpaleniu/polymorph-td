
project "WindowInputTest"
	kind "WindowedApp"
	language "C++"
	
	files { sourcePath .. "base/input/**.cpp",
			sourcePath .. "test/input/test_WindowInput_main.cpp",
			includePath .. "base/input/**.hpp" }

	configuration "windows"
		files { sourcePath .. "win32/input/**.cpp",
				includePath .. "win32/input/**.hpp" }
	
	includedirs { includePath .. "test" }
	
	links { "sys", "profiler", "gr", "ext", "concurrency", "text" }
