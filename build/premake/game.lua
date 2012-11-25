

game = 
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	end,

	doProject = function()
		project "game"
			kind "StaticLib"
			language "C++"
			
			files { projPath .. "/src/base/game/**.cpp" }
	end
}