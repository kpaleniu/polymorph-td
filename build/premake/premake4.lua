projPath = "../.."

solution "polymorph-td"
	configurations { "Debug", "Release" }
	includedirs { projPath .. "/include/base",
				  projPath .. "/include/game" }
	files { projPath .. "/src/game/**.cpp", 
			projPath .. "/src/base/**.cpp"}
	objdir ( projPath .. "/obj/" .. _ACTION )

	-- Generate own directory for each target
	location (projPath .. "/build/" .. _ACTION)
	targetdir (projPath .. "/bin")

	-- Boost includes and defines
	links { "boost_thread",
			"boost_chrono",
			"boost_system",
			"opengl32", }
	defines { "BOOST_THREAD_USE_LIB" }
	includedirs { ( os.getenv("BOOST_HOME") or "" ) .. "/include" }

	configuration "macosx"
		-- MacPorts default includes
		includedirs { "/opt/local/include" }
		libdirs { "/opt/local/lib" }

	configuration "Debug"
		flags { "Symbols", "ExtraWarnings" }
		defines { "_DEBUG" }
		libdirs { projPath .. "/lib/Debug" }

	configuration "Release"
		flags { "Optimize" }
		defines { "NDEBUG" }
		libdirs { projPath .. "/lib/Release" }

	-- Project for the actual game
	project "PolyMorphTD"
		kind "WindowedApp"
		language "C++"
		includedirs { projPath .. "/include/win32",
					  projPath .. "/include/opengl",
					  projPath .. "/include/wgl",
					  projPath .. "/include/boost" }
		files { projPath .. "/src/win32/**.cpp",
				projPath .. "/src/opengl/**.cpp",
				projPath .. "/src/wgl/**.cpp",
				projPath .. "/src/boost/**.cpp" }
		defines { "WIN32_LEAN_AND_MEAN" }

	-- Project for PolyMorphTD unit tests
	--[[
	project "PolyMorphTD-testrunner"
		kind "ConsoleApp"
		language "C++"
		files {
			"../../include/*.hpp",
			"../../tst/*.cpp"
		}
		excludes {
			"../../src/main.cpp"
		}
		links { "cppunit" }
	--]]
	
