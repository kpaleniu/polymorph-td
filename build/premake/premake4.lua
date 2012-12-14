
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
	trigger		= "test-build",
	description	= "Adds tests projects.",
}

projPath 		= "../.."
externalPath	= projPath .. "/external"

print("Graphics API")
print("  " .. _OPTIONS["gfx-api"] .. "\n")

print("Extensions API")
print("  " .. _OPTIONS["ext-api"] .. "\n")

print("Math API")
print("  " .. _OPTIONS["math-api"] .. "\n")

print("Image loading API")
print("  " .. _OPTIONS["il-api"] .. "\n")

if _OPTIONS["test-build"] then
	print("Building tests as well...\n")
end

-- Projects to build.
projects = { "ext",
			 "text",
			 "concurrency",
			 "gr",
			 "input",
			 "profiler",
			 "sys",
			 "math_proj",
			 "resource" }

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
	
	configuration "boost"
		includedirs { externalPath .. "/include/boost" } 
		libdirs { externalPath .. "/lib/boost" }
	
	configuration "libpng"
		includedirs { externalPath .. "/include/libpng" }
		libdirs { externalPath .. "/lib/libpng" }
	
	configuration "eigen"
		includedirs { externalPath .. "/include/eigen" }
	
	configuration "test-build"
		defines { "TEST_BUILD" }
	
	configuration "windows"
		defines { "WIN32_LEAN_AND_MEAN",
				  "WINVER=0x0501",
				  "_WIN32_WINNT=0x0501",
				  "_CRT_SECURE_NO_WARNINGS" }
	
	for _, proj in ipairs(projects) do
		print("Loading " .. proj)
		dofile(proj .. ".lua")
	end
	
	print()
	
	for _, proj in ipairs(projects) do
		print("Making project " .. proj)
		_G[proj].doProject()
		
		if _OPTIONS["test-build"] then
			if _G[proj].doTestProjects then
				print("Making test project for " .. proj)
				_G[proj].doTestProjects()
			end
		end
	end
	
	print()
	
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
	
