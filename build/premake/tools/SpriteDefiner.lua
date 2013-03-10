
project "SpriteDefiner"
	kind "WindowedApp"
	language "C++"
	
	includedirs { includePath .. "tools/SpriteDefiner" }
	
	files { sourcePath .. "tools/SpriteDefiner/**.cpp",
			includePath .. "tools/SpriteDefiner/**.hpp" }
	
	links { "sys", "input", "os", "resource", "gr", "profiler", "text", "ext", "concurrency" }
	
	useExternalAPI("il-api")
	useExternalAPI("gfx-api")
	useExternalAPI("math-api")
	useExternalAPI("ext-api")