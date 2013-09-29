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
	
	configuration {}
	
	pm.moduleDependencies
	{
		"ext",
	}