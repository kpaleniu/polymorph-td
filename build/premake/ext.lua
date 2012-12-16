
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
			
			configuration "boost"
				files { projPath .. "/src/boost/ext/**.cpp" }
				
			files { projPath .. "/src/base/ext/**.cpp" }
	end
}
