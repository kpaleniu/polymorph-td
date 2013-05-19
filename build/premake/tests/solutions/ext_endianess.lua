
solution "ext_endianess_tester"
	polymorphSolution()

	project "Test_ext_endianess"
		kind "ConsoleApp"
		language "C++"
		
		pm.cppFiles(
			testSourcePath .. "base/test_ext_endianess/",
			testIncludePath .. "base/test_ext_endianess/"
		)
		
		pm.moduleDependencies
		{
			"ext",
			"test"
		}
		