

input = 
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	
		configuration "windows"
			includedirs { projPath .. "/include/win32" }
	end,
	
	doProject = function()
		project "input"
			kind "StaticLib"
			language "C++"

			assert(input ~= nil)
			
			ext.doDeclarations()
			input.doDeclarations()

			files { projPath .. "/src/base/input/**.cpp" }

			configuration "windows"
				files { projPath .. "/src/win32/input/**.cpp" }
	end,
	
	doTestProjects = function()
		project "WindowInputTest"
			kind "WindowedApp"
			language "C++"
			
			links { "sys", "profiler", "gr", "ext", "concurrency", "text" }
			
			resource.doDeclarations()
			concurrency.doDeclarations()
			gr.doDeclarations()
			ext.doDeclarations()
			sys.doDeclarations()
			input.doDeclarations()
			profiler.doDeclarations()
			
			files { projPath .. "/src/base/input/**.cpp",
					projPath .. "/src/test/input/test_WindowInput_main.cpp" }

			configuration "windows"
				files { projPath .. "/src/win32/input/**.cpp" }
			
			includedirs { projPath .. "/include/test" }			
	end
}

