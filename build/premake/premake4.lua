solution "polymorph-td"
	configurations { "Debug", "Release" }
	includedirs "../../include"

	-- Generate own directory for each target
	location ("../" .. _ACTION)
	targetdir ("../../bin")
	-- My compiler defaults to llvm-gcc-4.2 :(
	--buildoptions { "-std=c++0x" }

	configuration "macosx"
		-- MacPorts default includes
		includedirs { "/opt/local/include" }
		libdirs { "/opt/local/lib" }

	configuration "Debug"
		flags { "Symbols", "ExtraWarnings" }

	configuration "Release"
		flags { "Optimize" }

	-- Project for the actual game
	project "PolyMorphTD"
		kind "ConsoleApp"
		language "C++"
		files {
			"../../include/*.hpp",
			"../../src/*.cpp"
		}
		links { "event" }
	
	-- Project for PolyMorphTD unit tests
	project "PolyMorphTD-testrunner"
		kind "ConsoleApp"
		language "C++"
		files {
			"../../include/*.hpp",
			"../../src/*.cpp",
			"../../tst/*.cpp"
		}
		excludes {
			"../../src/main.cpp"
		}
		links { "event", "cppunit" }
