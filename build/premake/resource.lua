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
			links { "png", "z" }
	end,

	doProject = function()
		assert(gr)
		assert(text)
		
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
		project "ImageReaderTest"
			kind "WindowedApp"
			language "C++"
			
			links { "gr", "ext", "concurrency", "text" }
			
			resource.doDeclarations()
			concurrency.doDeclarations()
			gr.doDeclarations()
			ext.doDeclarations()
			
			files { projPath .. "/src/libpng/resource/**.cpp",
					projPath .. "/src/base/resource/**.cpp",
					projPath .. "/src/test/resource/test_ImageReader_main.cpp",
					projPath .. "/src/test/gr/TestWindow.cpp" }
			
			includedirs { projPath .. "/include/test" }
			
	end
}
