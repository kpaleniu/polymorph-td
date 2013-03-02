--[[

Description:
	OS feature module.
	
OS specific.

--]]

project "os"
	kind "StaticLib"
	language "C++"
	
	links { "concurrency", "text" }
	
	configuration "windows"
		files { sourcePath .. "win32/os/**.cpp",
				includePath .. "win32/os/**.hpp" }