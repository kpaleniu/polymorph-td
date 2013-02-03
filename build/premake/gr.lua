

gr =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
		
		configuration {"windows", "opengl"}
			includedirs { projPath .. "/include/wgl" }
			links { "glew32", "glu32", "opengl32" }
			defines { "GLEW_STATIC" }

		configuration {"macosx", "opengl" }
			includedirs {
				"/opt/local/include",
				projPath .. "/include/cocoa"
			}
			libdirs { "/opt/local/libs" }
			links { "Cocoa.framework", "OpenGL.framework" }
	
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
			
			files {
				projPath .. "/src/base/gr/**.cpp",
				projPath .. "/include/base/gr/**.hpp"
		   	}
			
			configuration {"windows", "opengl"}
				files { projPath .. "/src/wgl/**.cpp" }

			configuration {"macosx", "opengl"}
				files {
					projPath .. "/src/cocoa/**.cpp",
					projPath .. "/src/cocoa/**.mm",
					projPath .. "/include/cocoa/**.hpp"
				}
			
			configuration "opengl"
				files {
					projPath .. "/src/opengl/**.cpp",
					projPath .. "/include/opengl/**.hpp"
			   	}
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
