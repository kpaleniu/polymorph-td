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
		
		pm.includedirs
		{
			includePath .. "win32"
		}
	
	configuration {}
	
	pm.moduleDependencies
	{
		"input",
		"os",
		"concurrency",
		"gr",
		"ext",
		"text"
	}
	