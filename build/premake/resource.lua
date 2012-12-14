
--
-- Resource project (currently empty).
--

resource =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	
		configuration "libpng"
			includedirs { projPath .. "/include/libpng" }
			links { externalPath .. "/lib/libpng/libpng" }
	end,

	doProject = function()
		project "resource"
			kind "StaticLib"
			language "C++"
			
			resource.doDeclarations()
			
			files { projPath .. "/src/libpng/res/**.cpp" }
			files { projPath .. "/src/base/res/**.cpp" }
	end,
	
	doTestProjects = function()
		project "LibPNGTest"
			kind "ConsoleApp"
			language "C++"
			
			resource.doDeclarations()
			
			files { projPath .. "/src/libpng/res/**.cpp",
					projPath .. "/src/base/res/**.cpp",
					projPath .. "/src/test/res/test_libpng_main.cpp" }
			
			includedirs { projPath .. "/include/test" }
			
	end
}
