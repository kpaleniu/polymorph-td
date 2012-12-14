

profiler =
{
	doDeclarations = function()
		includedirs { projPath .. "/include/base" }
	end,

	doProject = function()
		assert(concurrency)
		assert(ext)
		
		project "profiler"
			kind "StaticLib"
			language "C++"
			
			profiler.doDeclarations()
			concurrency.doDeclarations()
			ext.doDeclarations()
			
			files { projPath .. "/src/base/profiler/**.cpp" }
	end
}
