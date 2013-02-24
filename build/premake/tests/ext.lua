
project "EventTest"
	kind "ConsoleApp"
	language "C++"
	
	files { sourcePath .. "base/ext/**.cpp",
			sourcePath .. "test/ext/test_Event_main.cpp",
			
			includePath .. "base/ext/**.hpp" }
	
	configuration "boost"
		files { sourcePath .. "boost/ext/**.cpp",
				includePath .. "boost/ext/**.hpp" }
	
	links { "concurrency", "text" }