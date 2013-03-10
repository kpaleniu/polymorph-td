--[[

Description:
	Profiling module. In-built profiler.
	
Non-platform specific (excluding dependencies).

--]]

project "profiler"
	kind "StaticLib"
	language "C++"
		
	files { sourcePath .. "base/profiler/**.cpp",
			includePath .. "base/profiler/**.hpp" }
	
	useExternalAPI("ext-api")