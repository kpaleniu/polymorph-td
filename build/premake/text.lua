

text = 
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	end,
	
	doProject = function()
		assert(ext)
		
		project "text"
			kind "StaticLib"
			language "C++"
			
			text.doDeclarations()
			ext.doDeclarations()
			
			files { projPath .. "/src/base/text/**.cpp" }
	end
}
