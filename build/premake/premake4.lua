solution "polymorph-td"
	configurations { "Debug", "Release" }
	includedirs { "../../include" }
	files {"../../src/game/**.cpp"}
	objdir ("../../obj/" .. _ACTION)

	-- Generate own directory for each target
	location ("../" .. _ACTION)
	targetdir ("../../bin")

	-- Boost includes and defines
	links { "boost_thread",
			"boost_chrono",
			"boost_system", }
	defines { "BOOST_THREAD_USE_LIB" }
	includedirs { os.getenv("BOOST_HOME") .. "/include" }

	configuration "macosx"
		-- MacPorts default includes
		includedirs { "/opt/local/include" }
		libdirs { "/opt/local/lib" }

	configuration "Debug"
		flags { "Symbols", "ExtraWarnings" }
		defines { "_DEBUG" }
		libdirs { "../../lib/Debug" }

	configuration "Release"
		flags { "Optimize" }
		defines { "NDEBUG" }
		libdirs { "../../lib/Release" }

	-- Project for the actual game
	project "PolyMorphTD"
		kind "WindowedApp"
		language "C++"
		files { "../../include/**.hpp",
				"../../src/win32/**.cpp",
				"../../src/boost/**.cpp" }

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
	]]--
