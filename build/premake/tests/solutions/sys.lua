
solution "sys_tester"
	polymorphSolution()

	project "Test_sys"
		kind "WindowedApp"
		language "C++"
		
		pm.cppFiles(
			testSourcePath .. "base/test_sys/",
			testIncludePath .. "base/test_sys/"
		)
		
		configuration "windows"
			pm.cppFiles(
				testSourcePath .. "win32/test_sys/"
			)
			
		configuration {}
		
		pm.moduleDependencies 
		{
			"sys",
			"test"
		}