--[[

Description:
	Game module. Basic game application module.
	
Non-platform specific (excluding dependencies).

--]]

project "game"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/game/",
		includePath .. "base/game/"
	)
	
	pm.moduleDependencies
	{
		"resource",
		"gr",
		"math"
	}
	