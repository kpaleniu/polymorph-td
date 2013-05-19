
solution "io_tester"
	polymorphSolution()

	project "Test_io"
		kind "ConsoleApp"
		language "C++"
		
		pm.cppFiles(
			testSourcePath .. "base/test_io/",
			testIncludePath .. "base/test_io/"
		)
		
		pm.moduleDependencies 
		{
			"concurrency", 
			"ext", 
			"test", 
			"io" 
		}