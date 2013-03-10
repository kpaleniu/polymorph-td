--[[

Description:
	Resource module. Handles basic resource loading.
	
Image loading API specific.

--]]

project "resource"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/resource/**.cpp",
			includePath .. "base/resource/**.hpp" }
	
	configuration "libpng"
		files { sourcePath .. "libpng/resource/**.cpp",
				includePath .. "libpng/resource/**.hpp" }
	
	useExternalAPI("il-api")
	useExternalAPI("gfx-api")
	useExternalAPI("math-api")
	useExternalAPI("ext-api")