--[[

Description:
	File system module.
	
Platform specific.

--]]

project "filesystem"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/filesystem/",
		includePath .. "base/filesystem/"
	)
	
	pm.moduleDependencies { "io" }