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

print("Graphics API")
print("  " .. _OPTIONS["gfx-api"])

print("Extensions API")
print("  " .. _OPTIONS["ext-api"])

print("Math API")
print("  " .. _OPTIONS["math-api"])

print("Image loading API")
print("  " .. _OPTIONS["il-api"])

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
	"gui"
}

tests = 
{
	"ext",
	"game",
	"gr",
	"gui",
	"input",
	"math",
	"resource"
}

tools =
{
	"StringHasher"
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
	
	configuration "vs*"
		defines { "NO_CONSTEXPR" }
	
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
	configuration "boost"
		includedirs { externalPath .. "include/boost",
					  includePath .. "boost",
					  includePath .. "boost/ext" }
		libdirs { externalPath .. "lib/boost" }
	
	configuration "libpng"
		includedirs { externalPath .. "include/libpng",
					  includePath .. "libpng" }
		libdirs { externalPath .. "lib/libpng",
				  externalPath .. "lib/zlib" }
	
	configuration "eigen"
		includedirs { externalPath .. "include/eigen" }
	
	configuration "opengl"
		includedirs { includePath .. "opengl" }
		libdirs { externalPath .. "lib/glew" }
	
	configuration "windows"
		includedirs { includePath .. "win32" }
		defines { "WIN32_LEAN_AND_MEAN",
				  "WINVER=0x0501",
				  "_WIN32_WINNT=0x0501",
				  "_CRT_SECURE_NO_WARNINGS" }
	
	configuration("windows", "opengl")
		includedirs { includePath .. "wgl" }
	
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
		
		links (modules)
		
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
	
