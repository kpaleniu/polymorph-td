
project "DialogTest"
	kind "WindowedApp"
	language "C++"
	
	includedirs { projPath .. "/include/test" }
	
	links { "concurrency", "text", "ext" }
	
	configuration "windows"
		files { sourcePath .. "win32/os/**.cpp",
				sourcePath .. "test/win32/os/test_DialogTest_main.cpp",
				includePath .. "win32/os/**.hpp" }
	