
solution "filesystem_tester"

	polymorphSolution()

	project "Test_filesystem"
		kind "ConsoleApp"
		language "C++"
		
		pm.cppFiles(
			testSourcePath .. "base/test_filesystem/",
			testIncludePath .. "base/test_filesystem/"
		)
		
		pm.moduleDependencies
		{
			"concurrency", 
			"ext", 
			"test", 
			"io", 
			"filesystem" 
		}