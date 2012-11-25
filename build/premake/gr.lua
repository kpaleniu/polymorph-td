

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
	end
}
