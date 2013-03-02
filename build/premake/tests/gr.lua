
project "RenderPassTest"
	kind "WindowedApp"
	language "C++"
	
	includedirs { includePath .. "test" }
	
	links { "ext", "concurrency" }
	
	files { sourcePath .. "base/gr/**.cpp", 
			sourcePath .. "test/gr/test_RenderPass_main.cpp",
			sourcePath .. "test/gr/TestWindow.cpp",
			
			includePath .. "test/gr/**.hpp",
			includePath .. "test/gr/TestWindow.hpp" }
	
	configuration {"windows", "opengl"}
		files { sourcePath .. "wgl/**.cpp",
				includePath .. "wgl/**.hpp" }
		links { "glew32", "glu32", "opengl32" }
	
	configuration "opengl"
		files { sourcePath .. "opengl/**.cpp",
				includePath .. "opengl/**.hpp" }
	