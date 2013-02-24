--[[

Description:
	Math and vector algebra module.
	
Math API specific.

--]]

project "math"
	kind "StaticLib"
	language "C++"
	
	-- FIXME Should be refactored to check 'Eigen' config and put the files in eigen/math.
	files { sourcePath .. "base/math/**.cpp",  -- Will most likelly only hold headers in future.
			includePath .. "base/math/**.hpp" }