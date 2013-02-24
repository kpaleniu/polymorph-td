
project "GUITest"
	kind "WindowedApp"
	language "C++"
	
	files { sourcePath .. "base/gui/**.cpp",
			sourcePath .. "test/gui/test_GUI_main.cpp",
			
			includePath .. "base/gui/**.hpp" }
	
	includedirs { includePath .. "test" }
	
	links { "input", "sys", "profiler", "gr", "ext", "concurrency", "text" }