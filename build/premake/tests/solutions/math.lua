
solution "math_tester"
	polymorphSolution()

	project "Test_math"
		kind "ConsoleApp"
		language "C++"
		
		pm.cppFiles(
			testSourcePath .. "base/test_math/",
			testIncludePath .. "base/test_math/"
		)
		
		pm.moduleDependencies 
		{
			"test",
			"math"
		}