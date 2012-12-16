

concurrency =
{
	doDeclarations = function()
		configuration "boost"
			includedirs { projPath .. "/include/boost" }
		
		-- boost libraries need to be explicitly linked on 
		-- platforms not supporting #pragma comment
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
	end,
	
	doProject = function()
		assert(ext)
		assert(concurrency)
		
		project "concurrency"
			kind "StaticLib"
			language "C++"
			
			concurrency.doDeclarations()
			ext.doDeclarations()
			
			configuration "boost"
				files { projPath .. "/src/boost/concurrency/**.cpp" }
	end
}
