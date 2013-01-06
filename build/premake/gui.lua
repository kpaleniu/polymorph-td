

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
			
			links { "gr", "ext", "concurrency", "text", "resource" }
			
			gui.doDeclarations()
			concurrency.doDeclarations()
			resource.doDeclarations()
			gr.doDeclarations()
			ext.doDeclarations()
			
			
			includedirs { projPath .. "/include/test" }
			
			files { projPath .. "/src/base/gr/**.cpp", 
					projPath .. "/src/test/gui/test_GUI_main.cpp",
					projPath .. "/src/test/gr/TestWindow.cpp" }
	end
}
