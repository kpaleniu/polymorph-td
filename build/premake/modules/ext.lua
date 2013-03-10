--[[

Description:
	Language extensions module. Basic constructs used by many projects.
	
Extensions API specific (currently only Boost).

--]]
	
project "ext"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/ext/**.cpp",
			includePath .. "base/ext/**.hpp" }
	
	configuration "boost"
		files { sourcePath .. "boost/ext/**.cpp",
				includePath .. "boost/ext/**.hpp" }
	
	useExternalAPI("ext-api")