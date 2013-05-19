--[[

Description:
	Testing module, not part of main PolyMorph.
	
Since CppUnit is so derpy, use this instead.

--]]

project "test"
	kind "StaticLib"
	language "C++"
	
	pm.cppFiles(
		testSourcePath .. "base/test/",
		testIncludePath .. "base/test/"
	)
	
	pm.includedirs { testIncludePath .. "base" }
	
	pm.moduleDependencies { "ext" }