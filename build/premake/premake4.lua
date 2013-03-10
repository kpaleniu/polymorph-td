print()

-- Graphics API.
newoption 
{
	trigger 	= "gfx-api",
	value		= "API",
	description = "Graphics API.",
	allowed 	= { {"opengl",	"OpenGL"} }
}
_OPTIONS["gfx-api"] = _OPTIONS["gfx-api"] or "opengl"

-- Extensions API.
newoption
{
	trigger		= "ext-api",
	value		= "API",
	description = "Extensions API.",
	allowed		= { {"boost", 	"Boost"} } -- Future C++11 implementations might depricate this.
}
_OPTIONS["ext-api"] = _OPTIONS["ext-api"] or "boost"

-- Math API.
newoption
{
	trigger		= "math-api",
	value		= "API",
	description	= "Math API.",
	allowed		= { {"eigen", 	"Eigen"} }
}
_OPTIONS["math-api"] = _OPTIONS["math-api"] or "eigen"

-- Image loading API.
newoption
{
	trigger		= "il-api",
	value		= "API",
	description	= "Image loading API.",
	allowed		= { {"libpng",	"libPNG"} }
}
_OPTIONS["il-api"] = _OPTIONS["il-api"] or "libpng"

-- Build tests option.
newoption
{
	trigger		= "tests-build",
	description	= "Adds tests projects.",
}

-- Tool builds
newoption
{
	trigger		= "tools-build",
	description	= "Adds tools to build.",
}

projPath		= os.getcwd() .. "/../../"
externalPath	= projPath .. "external/"
includePath		= projPath .. "include/"
sourcePath		= projPath .. "src/"
modulePath		= os.getcwd() .. "/modules/"
testPath		= os.getcwd() .. "/tests/"
toolPath		= os.getcwd() .. "/tools/"

dofile("external.lua")

print()

if _OPTIONS["tests-build"] then
	print("Building tests.")
end

if _OPTIONS["tools-build"] then
	print("Building tools.")
end

print()

modules =
{
	"ext",
	"text",
	"concurrency",
	"sys",
	"gr",
	"game",
	"input",
	"profiler",
	"math",
	"resource",
	"gui",
	"os"
}

tests = 
{
	"ext",
	"game",
	"gr",
	"gui",
	"input",
	"math",
	"resource",
	"os"
}

tools =
{
	"StringHasher",
	"SpriteDefiner"
}

solution "polymorph-td"
	configurations { "Debug", "Release" }
	platforms { "Native", "x64" }
	targetdir (projPath .. "bin")
	
	includedirs { includePath .. "base/ext",
				  includePath .. "base"}
	
	-- Generate own build directories for each target
	location (projPath .. "build/" .. _ACTION)
	objdir ( projPath .. "obj/" .. _ACTION )
	
	-- C++0x/11 mode has to be explicitly enabled on some platforms
	configuration "not vs*"
		buildoptions { "-std=c++0x" }
		defines { "__GXX_EXPERIMENTAL_CXX0X__" }
	
	-- From 'configurations'
	configuration "Debug"
		flags { "Symbols", "ExtraWarnings" }
		defines { "_DEBUG" }
		libdirs { projPath .. "lib/Debug" }
	configuration "Release"
		flags { "Optimize" }
		defines { "NDEBUG" }
		libdirs { projPath .. "lib/Release" }
	
	-- API setup
	configuration "windows"
		includedirs { includePath .. "win32" }
		defines { --"WIN32_LEAN_AND_MEAN",
				  "WINVER=0x0501",
				  "_WIN32_WINNT=0x0501",
				  "_CRT_SECURE_NO_WARNINGS" }
	
	configuration "tools-build"
		defines { "TEST_BUILD" }
	--

	for _, module in ipairs(modules) do
		print("Module: " .. module)
		dofile(modulePath .. module .. ".lua")
	end
	print()
	if _OPTIONS["tests-build"] then
		for _, test in ipairs(tests) do
			print("Test: " .. test)
			dofile(testPath .. test .. ".lua")
		end
	end
	print()
	
	links (modules)
	
	if _OPTIONS["tools-build"] then
		for _, tool in ipairs(tools) do
			print("Tool: " .. tool)
			dofile(toolPath .. tool .. ".lua")
		end
	end
	print()
	
	-- Project for the actual game
	project "PolyMorphTD"
		kind "WindowedApp"
		language "C++"
		
		configuration "windows"
			includedirs { projPath .. "/include/win32" }
			files { projPath .. "/src/win32/win_main.cpp" }
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

		configuration {"macosx", "opengl"}
			links { "OpenGL.framework" }
		
	-- Project for PolyMorphTD unit tests
	--[[ Are we ever going to use this?
	project "PolyMorphTD-testrunner"
		kind "ConsoleApp"
		language "C++"
		files { projPath .. "/test/src/**.cpp" }
		includedirs { projPath .. "/include/mockup",
					  projPath .. "/test/include" }
		--links { "cppunit" }
	--]]
	
