--[[

Description:
	Profiling module. In-built profiler.
	
Non-platform specific (excluding dependencies).

--]]

--[[
project "profiler"
	kind "StaticLib"
	language "C++"
	
	vpaths
	{
		["Headers"] = includePath .. "base/profiler/*.hpp",
		["Inlines"] = includePath .. "base/profiler/*.inl",
		["Sources"] = sourcePath .. "base/profiler/*.cpp",
	}
	
	files { sourcePath .. "base/profiler/**.cpp",
			includePath .. "base/profiler/**.hpp" }
	
	useExternalAPI("ext-api")
--]]