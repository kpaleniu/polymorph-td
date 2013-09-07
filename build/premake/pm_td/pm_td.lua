
solution "PolyMorphTowerDefense"
	polymorphSolution()

	project "PolyMorphTD"
		kind "WindowedApp"
		language "C++"
		
		pm.cppFiles(
			sourcePath .. "base/pm_td/",
			includePath .. "base/pm_td/"
		)
		
		configuration "windows"
			pm.cppFiles(
				sourcePath .. "win32/pm_td/",
				includePath .. "win32/pm_td/"
			)
			
		configuration {}
		
		pm.moduleDependencies 
		{
			"concurrency", 
			"ext", 
			"math", 
			"io",
			"filesystem",
			"gr",
			"sys"
		}