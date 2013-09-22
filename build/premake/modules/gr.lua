--[[

Description:
	Graphics module. Wrapper for underlying graphics library.
	
GFX API specific.

--]]

project "gr"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/gr/",
		includePath .. "base/gr/"
	)
	
	configuration {"windows", "opengl"}
		pm.cppFiles(
			sourcePath .. "wgl/gr/",
			includePath .. "wgl/gr/"
		)
		
		pm.includedirs 
		{ 
			externalPath .. "include/glew",
			includePath .. "wgl" 
		}
		
		pm.defines 
		{ 
			"GLEW_STATIC" 
		}
		
		pm.libdirs 
		{ 
			externalPath .. "lib/glew" 
		}
		
		pm.links 
		{ 
			"glu32", 
			"opengl32",
			"glew32" 
		}

	configuration { "macosx", "opengl" }
		pm.cppFiles(
			sourcePath .. "cocoa/gr/",
			includePath .. "cocoa/gr/"
		)

		pm.includedirs
		{
			includePath .. "cocoa"
		}
		pm.links
		{
			"Cocoa.framework",
			"OpenGL.framework",
			"CoreVideo.framework"
		}

		
	configuration {"opengl"}
		pm.cppFiles(
			sourcePath .. "opengl/gr/",
			includePath .. "opengl/gr/"
		)
		
		pm.includedirs 
		{ 
			includePath .. "opengl" 
		}
	
	configuration {}
	
	pm.moduleDependencies 
	{ 
		"ext", 
		"concurrency",
		"math",
		"io",
	}
	
