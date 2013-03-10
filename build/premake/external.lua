
print("Graphics API")
print("  " .. _OPTIONS["gfx-api"])

print("Extensions API")
print("  " .. _OPTIONS["ext-api"])

print("Math API")
print("  " .. _OPTIONS["math-api"])

print("Image loading API")
print("  " .. _OPTIONS["il-api"])


local externalAPI =
{
	["gfx-api"] =
	{
		use = function()
			configuration { "opengl", "windows" }
				includedirs { externalPath .. "include/glew",
							  includePath .. "wgl" }
				defines { "GLEW_STATIC" }
				libdirs { externalPath .. "lib/glew" }
				links { "glew32" }
			
			configuration "opengl"
				includedirs { includePath .. "opengl" }
				links { "glu32", "opengl32" }
			
			configuration "*"
		end
	},
	["ext-api"] =
	{
		use = function()
			configuration "boost"
				includedirs { externalPath .. "include/boost",
							  includePath .. "boost" }
				defines { "BOOST_THREAD_USE_LIB" }
				libdirs { externalPath .. "lib/boost" }
			
			configuration { "boost", "Debug" }
				links { "boost_thread_d",
						"boost_chrono_d",
						"boost_system_d" }
						
			configuration { "boost", "Release" }
				links { "boost_thread",
						"boost_chrono",
						"boost_system" }
			
			configuration "*"
		end
	},
	["math-api"] =
	{
		use = function()
			configuration "eigen"
				includedirs { externalPath .. "include/eigen" }
			
			configuration "*"
		end
	},
	["il-api"] =
	{
		use = function()
			configuration "libpng"
				includedirs { externalPath .. "include/libpng",
							  includePath .. "libpng" }
				libdirs { externalPath .. "lib/libpng",
						  externalPath .. "lib/zlib" }
				links { "png", "z" }
			
			configuration "*"
		end
	}
}

function useExternalAPI(api)
	local apiUse = externalAPI[api]
	
	assert(apiUse ~= nil, "Cannot find api " .. api)
	apiUse.use()
end

