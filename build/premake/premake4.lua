
newoption 
{
	trigger 	= "with-opengl",
	description = "Uses OpenGL for rendering."
}

newoption
{
	trigger		= "with-boost",
	description = "Uses Boost libraries."
}

projPath = "../.."
boostDir = os.getenv("BOOST_HOME") or ""

solution "polymorph-td"
	configurations { "Debug", "Release" }
	platforms { "Native", "x64" }
	targetdir (projPath .. "/bin")
	
	-- Generate own build directories for each target
	location (projPath .. "/build/" .. _ACTION)
	objdir ( projPath .. "/obj/" .. _ACTION )
	
	-- Game and engine.
	files { projPath .. "/src/game/**.cpp", 
			projPath .. "/src/base/**.cpp" }
	includedirs { projPath .. "/include/base",
				  projPath .. "/include/game" }
	
	-- C++0x/11 mode has to be explicitly enabled on some platforms
	configuration "not vs*"
		buildoptions { "-std=c++0x" }
	
	-- From 'configurations'.
	configuration "Debug"
		flags { "Symbols", "ExtraWarnings" }
		defines { "_DEBUG" }
		libdirs { projPath .. "/lib/Debug" }
	
	configuration "Release"
		flags { "Optimize" }
		defines { "NDEBUG" }
		libdirs { projPath .. "/lib/Release" }
	
	configuration "with-boost"
		includedirs { projPath .. "/include/boost",
					  boostDir .. "/include" } 
		libdirs { boostDir .. "/lib" }
		files { projPath .. "/src/boost/**.cpp" }
	
	-- boost libraries need to be explicitly linked on 
	-- platforms not supporting #pragma comment
	configuration "with-boost and not vs*"
		defines { "BOOST_THREAD_USE_LIB" }
		links { "boost_thread",
				"boost_chrono",
				"boost_system" }
	
	-- Project for the actual game
	project "PolyMorphTD"
		kind "WindowedApp"
		language "C++"
		
		configuration "with-opengl"
			includedirs { projPath .. "/include/opengl" }
			links { "opengl32" }
			files { projPath .. "/src/opengl/**.cpp" }
		
		configuration "windows"
			includedirs { projPath .. "/include/win32" }
			defines { "WIN32_LEAN_AND_MEAN" }
			files { projPath .. "/src/win32/**.cpp" }
			flags { "WinMain" }
		
		configuration {"windows", "with-opengl"}
			includedirs { projPath .. "/include/wgl" }
			files { projPath .. "/src/wgl/**.cpp" }
		
		configuration "macosx"
			-- MacPorts default includes
			includedirs { "/opt/local/include" }
			libdirs { "/opt/local/lib" }
	
	-- Project for PolyMorphTD unit tests
	project "PolyMorphTD-testrunner"
		kind "ConsoleApp"
		language "C++"
		files { projPath .. "/test/src/**.cpp" }
		includedirs { projPath .. "/include/mockup",
					  projPath .. "/test/include" }
		--links { "cppunit" }
	
	
