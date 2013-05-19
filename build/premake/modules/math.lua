--[[

Description:
	Math and vector algebra module.
	
Math API specific.

--]]

project "math"
	kind "StaticLib"
	language "C++"
	
	-- FIXME Should be refactored to check 'Eigen' config and put the files in eigen/math.
	pm.cppFiles(
		sourcePath .. "base/math/",
		includePath .. "base/math/"
	)
	
	configuration "eigen"
		pm.includedirs 
		{ 
			externalPath .. "include/eigen"
		}
	
	pm.moduleDependencies
	{
		"ext"
	}