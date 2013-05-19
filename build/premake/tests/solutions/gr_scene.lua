
solution "gr_scene_tester"
	polymorphSolution()

	project "Test_gr_scene"
		kind "WindowedApp"
		language "C++"
		
		pm.cppFiles(
			testSourcePath .. "base/test_gr_scene/",
			testIncludePath .. "base/test_gr_scene/"
		)
		
		configuration {"windows", "opengl"}
			pm.cppFiles(
				testSourcePath .. "wgl/gr/",
				testIncludePath .. "wgl/gr/"
			)
		
		configuration "windows"
			pm.cppFiles(
				testSourcePath .. "win32/test_gr_scene"
			)
			
		configuration {}
		
		pm.moduleDependencies 
		{
			"concurrency", 
			"ext", 
			"test", 
			"io",
			"gr",
		}