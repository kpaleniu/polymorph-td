
solution "filesystem_tester"
	includedirs { testIncludePath .. "base" }
	
	useExternalAPI("ext-api")
	
	polymorphSolution()
	
	addModule("concurrency")
	addModule("ext")
	addModule("io")
	addModule("filesystem")
	addModule("test")

	project "Test_filesystem"
		kind "ConsoleApp"
		language "C++"
		
		vpaths
		{
			["Headers"] = testIncludePath .. "base/test_filesystem/*.hpp",
			["Inlines"] = testIncludePath .. "base/test_filesystem/*.inl",
			["Sources"] = testSourcePath .. "base/test_filesystem/*.cpp",
		}
		
		files
		{
			testIncludePath .. "base/test_filesystem/*.hpp",
			testIncludePath .. "base/test_filesystem/*.inl",
			testSourcePath .. "base/test_filesystem/*.cpp",
		}
		
		
		links { "concurrency", "ext", "test", "io", "filesystem" }