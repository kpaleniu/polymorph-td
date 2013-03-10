--[[

Description:
	GUI module. Uses Graphics and UI systems to create GUI.
	
Non-platform specific (excluding dependencies).

--]]

project "gui"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/gui/**.cpp",
			includePath .. "base/gui/**.hpp" }
	
	useExternalAPI("gfx-api")
	useExternalAPI("ext-api")
