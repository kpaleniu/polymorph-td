

game = 
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	end,

	doProject = function()
		project "game"
			kind "StaticLib"
			language "C++"
			
			ext.doDeclarations()
			gr.doDeclarations()
			sys.doDeclarations()
			game.doDeclarations()
			
			files { projPath .. "/src/base/game/**.cpp" }
	end,
	
	doTestProjects = function()
		project "GameTest"
			kind "WindowedApp"
			language "C++"
			
			links { "gr", "ext", "concurrency", "text" }
			
			concurrency.doDeclarations()
			ext.doDeclarations()
			gr.doDeclarations()
			sys.doDeclarations()
			
			includedirs { projPath .. "/include/test" }
			
			files { projPath .. "/src/base/game/**.cpp",
					projPath .. "/src/test/gr/TestWindow.cpp",
					projPath .. "/src/test/game/test_Game_main.cpp" }
			
	end
}