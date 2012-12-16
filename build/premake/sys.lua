

sys =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
		
		configuration "boost"
			includedirs { projPath .. "/include/boost" }
		
		configuration "windows"
			includedirs { projPath .. "/include/win32" }
	end,
	
	doProject = function()
		project "sys"
			kind "StaticLib"
			language "C++"

			assert(gr ~= nil)
			assert(input ~= nil)
			assert(concurrency ~= nil)

			ext.doDeclarations()
			gr.doDeclarations()
			input.doDeclarations()
			concurrency.doDeclarations()
			sys.doDeclarations()
			
			files { projPath .. "/src/base/sys/**.cpp" }
			
			configuration "boost"
				files { projPath .. "/src/boost/sys/**.cpp" }
			
			configuration "windows"
				files { projPath .. "/src/win32/sys/**.cpp" }
	end
}

