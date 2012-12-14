

math_proj =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
		
		configuration { "eigen" }
			includedirs { externalPath .. "/include/eigen" }
		
	end,
	
	doProject = function()
		project "math"
			kind "StaticLib"
			language "C++"
			
			math_proj.doDeclarations()
			
			files { projPath .. "/src/base/math/**.cpp" } -- Will most likelly only hold headers in future.
	end,
	
	doTestProjects = function()
		project "MathTest"
			kind "ConsoleApp"
			language "C++"
			
			math_proj.doDeclarations()
			
			files { projPath .. "/src/base/math/**.cpp", 
					projPath .. "/src/test/math/test_Math_main.cpp" }
			
			includedirs { projPath .. "/include/test" }
			
			
	end
}