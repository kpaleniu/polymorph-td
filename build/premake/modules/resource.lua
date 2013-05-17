--[[

Description:
	Resource module. Handles basic resource loading.
	
Image loading API specific.

--]]

project "resource"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/resource/",
		includePath .. "base/resource/"
	)
	
	configuration "libpng"
		pm.cppFiles(
			sourcePath .. "libpng/resource/",
			includePath .. "libpng/resource/"
		)
		
		pm.includedirs
		{ 
			externalPath .. "include/libpng",
			 includePath .. "libpng" 
		}
		
		pm.libdirs
		{ 
			externalPath .. "lib/libpng",
			externalPath .. "lib/zlib" 
		}
		
		pm.links 
		{ 
			"png", 
			"z" 
		}
	
	configuration {}
	
	pm.moduleDependencies
	{
		"ext",
		"gr",
	}