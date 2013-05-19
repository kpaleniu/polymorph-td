--[[

Description:
	GUI module. Uses Graphics and UI systems to create GUI.
	
Non-platform specific (excluding dependencies).

--]]

project "gui"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/gui/",
		includePath .. "base/gui/"
	)
	
	pm.moduleDependencie
	{
		"ext",
		"gr"
	}