

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
			
			links { "ext", "concurrency" }
			
			concurrency.doDeclarations()
			ext.doDeclarations()
			gr.doDeclarations()
			
			------- TODO
	end
}