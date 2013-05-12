--[[

Description:
	Concurrency module. Basic concurrency handling.
	
Extensions API specific (currently only Boost but may be removed as C++11 
thread libraries will be implemented).

--]]

project "concurrency"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		sourcePath .. "base/concurrency/",
		includePath .. "base/concurrency/"
	)
	
	configuration "boost"
		pm.cppFiles(
			sourcePath .. "boost/concurrency/",
			includePath .. "boost/concurrency/"
		)
		
		pm.defines { "BOOST_THREAD_USE_LIB" }
		pm.libdirs { externalPath .. "lib/boost" }
		pm.includedirs { externalPath .. "include/boost",
						 includePath .. "boost"}
	
	configuration { "boost", "Debug" }
		pm.links { "boost_thread_d",
				   "boost_chrono_d",
				   "boost_system_d" }
				
	configuration { "boost", "Release" }
		pm.links { "boost_thread",
				   "boost_chrono",
				   "boost_system" }
	
	pm.moduleDependencies { "ext" }