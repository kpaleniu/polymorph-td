
--
-- Basic extensions project.
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
	end,
	
	doTestProjects = function()
		project "EventTest"
			kind "ConsoleApp"
			language "C++"
			
			links { "concurrency" }
			
			files { projPath .. "/src/base/ext/**.cpp" }
			files {	projPath .. "/src/test/ext/test_Event_main.cpp" }
			
			ext.doDeclarations()
			concurrency.doDeclarations()
			
			configuration "boost"
				files { projPath .. "/src/boost/ext/**.cpp" }
	end
}
