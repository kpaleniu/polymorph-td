

gui =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	end,
	
	doProject = function()
		assert(ext)
		
		project "gui"
			kind "StaticLib"
			language "C++"
			
			concurrency.doDeclarations() -- Used in Debug
			gr.doDeclarations()
			ext.doDeclarations()
			gui.doDeclarations()
			
			files { projPath .. "/src/base/gui/**.cpp" }
	end,
	
	doTestProjects = function()
		project "GUITest"
			kind "WindowedApp"
			language "C++"
			
			links { "input", "sys", "profiler", "gr", "ext", "concurrency", "text" }
			
			includedirs { projPath .. "/include/test" }	
			
			files { projPath .. "/src/base/gui/**.cpp",
					projPath .. "/src/test/gui/test_GUI_main.cpp" }
			
			concurrency.doDeclarations()
			gr.doDeclarations()
			ext.doDeclarations()
			sys.doDeclarations()
			input.doDeclarations()
			profiler.doDeclarations()

			configuration "windows"
				files { projPath .. "/src/win32/input/**.cpp" }
	end
}
