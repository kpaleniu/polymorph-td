--[[

Description:
	System module. A system is basically a thread with utilities.
	
Platform specific.

--]]

project "sys"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/sys/**.cpp",
			includePath .. "base/sys/**.hpp" }
		
	configuration "windows"
		files { sourcePath .. "win32/sys/**.cpp",
				includePath .. "win32/sys/**.hpp" }
