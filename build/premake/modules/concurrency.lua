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

	configuration { "boost", "not vs*", "Debug" }
			defines { "BOOST_THREAD_USE_LIB" }
			links { "boost_thread_d",
					"boost_chrono_d",
					"boost_system_d" }
	
	configuration { "boost", "not vs*", "Release" }
			defines { "BOOST_THREAD_USE_LIB" }
			links { "boost_thread",
					"boost_chrono",
					"boost_system" }
