
solution "filesystem_tester"
	includedirs { testIncludePath .. "base" }
	
	externalAPIs("ext-api")
	
	polymorphSolution()
	
	modules("concurrency")
	modules("ext")
	modules("io")
	modules("filesystem")
	modules("test")

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