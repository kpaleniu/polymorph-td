

profiler =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	end,

	doProject = function()
		assert(concurrency)
		
		project "profiler"
			kind "StaticLib"
			language "C++"
			
			profiler.doDeclarations()
			concurrency.doDeclarations()
			ext.doDeclarations()
			
			files { projPath .. "/src/base/profiler/**.cpp" }
	end
}
