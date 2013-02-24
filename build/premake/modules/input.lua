--[[

Description:
	Input module. Uses OS / window to handle IO events.
	
Platform specific.

--]]

project "input"
	kind "StaticLib"
	language "C++"

	files { sourcePath .. "base/input/**.cpp",
			includePath .. "base/input/**.hpp" }

	configuration "windows"
		files { sourcePath .. "win32/input/**.cpp",
				includePath .. "win32/input/**.hpp" }
