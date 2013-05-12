--[[

Description:
	Input module. Uses OS / window to handle IO events.
	
Platform specific.

--]]

project "input"
	kind "StaticLib"
	language "C++"

	pm.cppFiles(
		sourcePath .. "base/input/",
		includePath .. "base/input/"
	)
	
	configuration "windows"
		pm.cppFiles(
			sourcePath .. "win32/input/",
			includePath .. "win32/input/"
		)
	
	configuration {}
	
	pm.moduleDependencies
	{
		"ext"
	}