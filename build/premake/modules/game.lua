--[[

Description:
	Game module. Basic game application module.
	
Non-platform specific (excluding dependencies).

--]]

project "game"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/game/**.cpp",
			includePath .. "base/game/**.hpp" }
	
	useExternalAPI("il-api")
	useExternalAPI("gfx-api")
	useExternalAPI("math-api")
	useExternalAPI("ext-api")