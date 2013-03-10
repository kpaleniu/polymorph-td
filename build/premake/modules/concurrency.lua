--[[

Description:
	Concurrency module. Basic concurrency handling.
	
Extensions API specific (currently only Boost but may be removed as C++11 
thread libraries will be implemented).

--]]

project "concurrency"
	kind "StaticLib"
	language "C++"
	
	files { sourcePath .. "base/concurrency/**.cpp",
			includePath .. "base/concurrency/**.hpp" }
	
	configuration "boost"
		files { sourcePath .. "boost/concurrency/**.cpp",
				includePath .. "boost/concurrency/**.hpp" }
	
	useExternalAPI("ext-api")