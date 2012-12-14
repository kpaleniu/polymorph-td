
--
-- Basic extensions project.
-- 
-- Empty project as there're only headers atm.
--

ext = 
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base/ext" }
	
		configuration "boost"
			includedirs { projPath .. "/include/boost/ext" }
	end,
	
	doProject = function()
		assert(concurrency)
		
		project "ext"
			kind "StaticLib"
			language "C++"
			
			ext.doDeclarations()
			concurrency.doDeclarations()
			
			files { projPath .. "/src/base/ext/**.cpp" }
	end
}
