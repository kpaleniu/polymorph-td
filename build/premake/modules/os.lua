--[[

Description:
	OS feature module.
	
OS specific.

--]]

project "os"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/os/",
		includePath .. "base/os/"
	)
	
	configuration "windows"
		pm.cppFiles(
			sourcePath .. "win32/os/",
			includePath .. "win32/os/"
		)
		
		pm.includedirs 
		{
			includePath .. "win32"
		}
		
	configuration {}
	
	pm.moduleDependencies
	{
		"ext",
		"concurrency"
	}