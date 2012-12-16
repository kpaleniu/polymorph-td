

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
	end
}

