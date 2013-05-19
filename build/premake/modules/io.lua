--[[

Description:
	IO module.
	
Platform specific.

--]]

project "io"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/io/",
		includePath .. "base/io/"
	)
	
	pm.moduleDependencies { "ext" }