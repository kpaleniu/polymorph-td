--
-- Resource project (currently empty).
--

resource =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
		
		configuration "boost"
			includedirs { projPath .. "/include/boost" }
		
		configuration "libpng"
			includedirs { projPath .. "/include/libpng" }
			links { externalPath .. "/lib/libpng/libpng" }
	end,

	doProject = function()
		assert(gr)
		
		project "resource"
			kind "StaticLib"
			language "C++"
		
			ext.doDeclarations()
			gr.doDeclarations()
			resource.doDeclarations()
			
			files { projPath .. "/src/libpng/resource/**.cpp" }
			files { projPath .. "/src/base/resource/**.cpp" }
	end,
	
	doTestProjects = function()
		project "LibPNGTest"
			kind "ConsoleApp"
			language "C++"
			
			gr.doDeclarations()
			resource.doDeclarations()
			
			files { projPath .. "/src/libpng/resource/**.cpp",
					projPath .. "/src/base/resource/**.cpp",
					projPath .. "/src/test/resource/test_libpng_main.cpp" }
			
			includedirs { projPath .. "/include/test" }
			
	end
}
