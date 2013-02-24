
project "GameTest"
	kind "WindowedApp"
	language "C++"
	
	files { sourcePath .. "base/game/**.cpp",
			sourcePath .. "test/gr/TestWindow.cpp",
			sourcePath .. "test/game/test_Game_main.cpp",
			
			includePath .. "base/game/**.hpp",
			includePath .. "test/TestWindow.hpp" }
	
	includedirs { projPath .. "/include/test" }
	
	links { "gr", "ext", "concurrency", "text" }