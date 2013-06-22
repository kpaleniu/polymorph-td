--[[

Description:
	Language extensions module. Basic constructs used by many projects.
	
Extensions API specific (currently only Boost).

--]]

project "ext"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/ext/",
		includePath .. "base/ext/"
	)
	
	pm.includedirs 
	{
		includePath .. "base/ext" 
	}
	
	configuration "boost"
		pm.cppFiles( 
			sourcePath .. "boost/ext/",
			includePath .. "boost/ext/" 
		)
		
		pm.includedirs 
		{ 
			includePath .. "boost/ext",
			externalPath .. "include/boost" 
		}
	
	configuration "std"
		pm.cppFiles(
			sourcePath .. "std/ext/",
			includePath .. "std/ext/"
		)
		
		pm.includedirs
		{
			includePath .. "std/ext"
		}
	
	configuration {}