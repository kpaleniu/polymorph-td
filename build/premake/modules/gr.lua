--[[

Description:
	Graphics module. Wrapper for underlying graphics library.
	
GFX API specific.

--]]

project "gr"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/gr/**.cpp",
			includePath .. "base/gr/**.hpp" }
	
	configuration {"windows", "opengl"}
		files { sourcePath .. "wgl/**.cpp",
				includePath .. "wgl/**.hpp" }
	
	configuration "opengl"
		files { sourcePath .. "opengl/**.cpp",
				includePath .. "opengl/**.hpp" }
	
	useExternalAPI("gfx-api")
	useExternalAPI("math-api")
	useExternalAPI("ext-api")
