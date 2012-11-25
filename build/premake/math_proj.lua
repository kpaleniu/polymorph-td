

math_proj =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	end,
	
	doProject = function()
		project "math"
			kind "StaticLib"
			language "C++"
			
			math_proj.doDeclarations()
			
			files { projPath .. "/src/base/math/**.cpp" }
	end
}