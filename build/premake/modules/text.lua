--[[

Description:
	Text utility module.
	
Non-platform specific (excluding dependencies).

--]]

project "text"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/text/",
		includePath .. "base/text/"
	)
	
	pm.moduleDependencies
	{
		"ext"
	}