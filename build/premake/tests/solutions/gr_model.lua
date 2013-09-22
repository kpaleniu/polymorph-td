
solution "gr_model_tester"
	polymorphSolution()

	project "Test_gr_model"
		kind "WindowedApp"
		language "C++"
		
		pm.cppFiles(
			testSourcePath .. "base/test_gr_model/",
			testIncludePath .. "base/test_gr_model/"
		)
		
		configuration {"windows", "opengl"}
			pm.cppFiles(
				testSourcePath .. "wgl/gr/",
				testIncludePath .. "wgl/gr/"
			)
			
			pm.includedirs 
			{
				testIncludePath .. "wgl"
			}
		
		configuration {"windows", "opengl"}
			pm.cppFiles(
				testSourcePath .. "cocoa/gr/",
				testIncludePath .. "cocoa/gr/"
			)
			
			pm.includedirs 
			{
				testIncludePath .. "cocoa"
			}

		configuration "windows"
			pm.cppFiles(
				testSourcePath .. "win32/test_gr_model/"
			)

		configuration "macosx"
			pm.cppFiles(
				testSourcePath .. "cocoa/test_gr_model/"
			)
			
		configuration {}
		
		pm.moduleDependencies 
		{
			"concurrency", 
			"ext", 
			"test", 
			"math", 
			"io",
			"filesystem",
			"gr",
		}
