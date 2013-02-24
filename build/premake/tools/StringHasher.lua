
project "StringHasher"
	kind "ConsoleApp"
	language "C++"
	
	files { sourcePath .. "tools/StringHasher/**.cpp",
			includePath .. "tools/StringHasher/**.hpp" }
	
	links { "text" }