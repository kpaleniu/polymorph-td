--[[

Description:
	OS feature module.
	
OS specific.

--]]

project "os"
	kind "StaticLib"
	language "C++"
	
	vpaths
	{
		["Headers"] = includePath .. "base/os/*.hpp",
		["Inlines"] = includePath .. "base/os/*.inl",
		["Sources"] = sourcePath .. "base/os/*.cpp",
		
		["Headers/Win32"] = includePath .. "win32/os/*.hpp",
		["Inlines/Win32"] = includePath .. "win32/os/*.inl",
		["Sources/Win32"] = sourcePath .. "win32/os/*.cpp",
	}
	
	configuration "windows"
		files { sourcePath .. "win32/os/**.cpp",
				includePath .. "win32/os/**.hpp" }
	
	useExternalAPI("il-api")
	useExternalAPI("gfx-api")
	useExternalAPI("math-api")
	useExternalAPI("ext-api")