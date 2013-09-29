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
			"glew32" 
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
		
		pm.links 
		{ 
			"glu32", 
			"opengl32" 
		}
	
	configuration {}
	
	pm.moduleDependencies 
	{ 
		"ext", 
		"concurrency",
		"math",
		"io",
		"resource"
	}
	