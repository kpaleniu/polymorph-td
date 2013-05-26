--[[

Description:
	Math and vector algebra module.
	
Math API specific.

--]]

project "math"
	kind "StaticLib"
	language "C++"
	
	configuration "eigen"
		pm.cppFiles(
			sourcePath .. "eigen/math/",
			includePath .. "eigen/math/"
		)
		pm.includedirs 
		{ 
			externalPath .. "include/eigen",
			includePath .. "eigen"
		}
		
	configuration "math_ext"
		pm.cppFiles(
			sourcePath .. "math_ext/math/",
			includePath .. "math_ext/math/"
		)
		pm.includedirs
		{
			includePath .. "math_ext"
		}
	
	pm.moduleDependencies
	{
		"ext"
	}