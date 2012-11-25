

concurrency =
{
	doDeclarations = function()
		configuration "with-boost"
			includedirs { projPath .. "/include/boost" }
		
		-- boost libraries need to be explicitly linked on 
		-- platforms not supporting #pragma comment
		configuration { "with-boost", "not vs*" }
			defines { "BOOST_THREAD_USE_LIB" }
			links { "boost_thread",
					"boost_chrono",
					"boost_system" }
		
	end,
	
	doProject = function()
		assert(ext)
		
		project "concurrency"
			kind "StaticLib"
			language "C++"
			
			concurrency.doDeclarations()
			ext.doDeclarations()
			
			configuration "with-boost"
				files { projPath .. "/src/boost/concurrency/**.cpp" }
	end
}
