

gr =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
		
		configuration {"windows", "with-opengl"}
			includedirs { projPath .. "/include/wgl" }
	
		configuration "with-opengl"
			includedirs { projPath .. "/include/opengl" }
			defines { "GLEW_STATIC" }
	end,
	
	doProject = function()
		assert(ext)
		
		project "gr"
			kind "StaticLib"
			language "C++"
			
			gr.doDeclarations()
			ext.doDeclarations()
			
			files { projPath .. "/src/base/gr/**.cpp" }
			
			configuration {"windows", "with-opengl"}
				files { projPath .. "/src/wgl/**.cpp" }
				links { "glew32", "glu32", "opengl32" }
			
			configuration "with-opengl"
				files { projPath .. "/src/opengl/**.cpp" }
	end,
	
	doTestProjects = function()
		project "RenderPassTest"
			kind "WindowedApp"
			language "C++"
			
			links { "ext", "concurrency" }
			
			concurrency.doDeclarations() -- Used in Debug
			ext.doDeclarations()
			gr.doDeclarations()
			
			files { projPath .. "/src/base/gr/**.cpp", 
					projPath .. "/src/test/gr/test_RenderPass_main.cpp",
					projPath .. "/src/test/gr/TestWindow.cpp" }
			
			includedirs { projPath .. "/include/test" }
			
			configuration {"windows", "with-opengl"}
				files { projPath .. "/src/wgl/**.cpp" }
				links { "glew32", "glu32", "opengl32" }
			
			configuration "with-opengl"
				files { projPath .. "/src/opengl/**.cpp" }
			
			
	end
}
