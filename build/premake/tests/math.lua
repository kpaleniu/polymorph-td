
project "MathTest"
	kind "ConsoleApp"
	language "C++"
	
	files { sourcePath .. "base/math/**.cpp", 
			sourcePath .. "test/math/test_Math_main.cpp",
			
			includePath .. "base/math/**.hpp" }
	
	includedirs { projPath .. "/include/test" }