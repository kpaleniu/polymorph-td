--[[

Description:
	Text utility module.
	
Non-platform specific (excluding dependencies).

--]]

project "text"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/text/**.cpp",
			includePath .. "base/text/**.hpp" }
	
	useExternalAPI("ext-api")