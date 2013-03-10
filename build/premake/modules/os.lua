--[[

Description:
	OS feature module.
	
OS specific.

--]]

project "os"
	kind "StaticLib"
	language "C++"
	
	configuration "windows"
		files { sourcePath .. "win32/os/**.cpp",
				includePath .. "win32/os/**.hpp" }
	
	useExternalAPI("il-api")
	useExternalAPI("gfx-api")
	useExternalAPI("math-api")
	useExternalAPI("ext-api")