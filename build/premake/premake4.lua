
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
	
	-- Assert, Debug, etc. includes
	includedirs { projPath .. "/include/base/ext" }
	
	-- Generate own build directories for each target
	location (projPath .. "/build/" .. _ACTION)
	objdir ( projPath .. "/obj/" .. _ACTION )
	
	-- C++0x/11 mode has to be explicitly enabled on some platforms
	configuration "not vs*"
		buildoptions { "-std=c++0x" }
		defines { "__GXX_EXPERIMENTAL_CXX0X__" }
	
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
		includedirs { boostDir .. "/include" } 
		libdirs { boostDir .. "/lib" }
	
	
	configuration "windows"
		defines { "WIN32_LEAN_AND_MEAN",
				  "WINVER=0x0501",
				  "_WIN32_WINNT=0x0501",
				  "_CRT_SECURE_NO_WARNINGS" }
	
	projects = { "ext",
				 "text",
				 "concurrency",
				 "gr",
				 "input",
				 "profiler",
				 "sys",
				 "math_proj" }
	
	for _, proj in ipairs(projects) do
		print("Loading " .. proj)
		dofile(proj .. ".lua")
	end
	
	for _, proj in ipairs(projects) do
		print("Making project " .. proj)
		_G[proj].doProject()
	end
	
	-- Project for the actual game
	project "PolyMorphTD"
		kind "WindowedApp"
		language "C++"
		
		links (projects)
		
		for _, proj in ipairs(projects) do
			_G[proj].doDeclarations()
		end
		
		configuration "windows"
			includedirs { projPath .. "/include/win32" }
			files { projPath .. "/src/win32/**.cpp" }
			flags { "WinMain" }
		
		configuration "macosx"
			-- MacPorts default includes
			includedirs {
				"/opt/local/include",
				projPath .. "/include/cocoa/" }
			files {
				projPath .. "/src/osx/**.cpp",
				projPath .. "/src/osx/**.mm"
		   	}

			libdirs { "/opt/local/lib" }
			links { "Cocoa.framework" }

		configuration {"macosx", "with-opengl"}
			links { "OpenGL.framework" }

	-- Project for PolyMorphTD unit tests
	--[[
	project "PolyMorphTD-testrunner"
		kind "ConsoleApp"
		language "C++"
		files { projPath .. "/test/src/**.cpp" }
		includedirs { projPath .. "/include/mockup",
					  projPath .. "/test/include" }
		--links { "cppunit" }
	--]]
	
