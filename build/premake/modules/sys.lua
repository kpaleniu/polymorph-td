--[[

Description:
	System module. A system is basically a thread with utilities.
	
Platform specific.

--]]

project "sys"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/sys/",
		includePath .. "base/sys/"
	)
	
	configuration "windows"
		pm.cppFiles(
			sourcePath .. "win32/sys/",
			includePath .. "win32/sys/"
		)
	
	pm.moduleDependencies
	{
		"resource",
		"gr",
		"math",
		"ext"
	}
	