

gr =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
		
		configuration {"windows", "opengl"}
			includedirs { projPath .. "/include/wgl" }
			defines { "GLEW_STATIC" }
	
		configuration "opengl"
			includedirs { projPath .. "/include/opengl" }
	end,
	
	doProject = function()
		assert(ext)
		
		project "gr"
			kind "StaticLib"
			language "C++"
			
			assert(ext)
			assert(concurrency)
			assert(math_proj)
			
			concurrency.doDeclarations() -- Used in Debug
			gr.doDeclarations()
			ext.doDeclarations()
			math_proj.doDeclarations()
			
			files { projPath .. "/src/base/gr/**.cpp" }
			
			configuration {"windows", "opengl"}
				files { projPath .. "/src/wgl/**.cpp" }
				links { "glew32", "glu32", "opengl32" }
			
			configuration "opengl"
				files { projPath .. "/src/opengl/**.cpp" }
	end,
	
	doTestProjects = function()
		project "RenderPassTest"
			kind "WindowedApp"
			language "C++"
			
			assert(ext)
			assert(concurrency)
			assert(math_proj)
			
			links { "ext", "concurrency" }
			
			concurrency.doDeclarations() -- Used in Debug
			ext.doDeclarations()
			gr.doDeclarations()
			math_proj.doDeclarations()
			
			files { projPath .. "/src/base/gr/**.cpp", 
					projPath .. "/src/test/gr/test_RenderPass_main.cpp",
					projPath .. "/src/test/gr/TestWindow.cpp" }
			
			includedirs { projPath .. "/include/test" }
			
			configuration {"windows", "opengl"}
				files { projPath .. "/src/wgl/**.cpp" }
				links { "glew32", "glu32", "opengl32" }
			
			configuration "opengl"
				files { projPath .. "/src/opengl/**.cpp" }
			
			
	end
}
