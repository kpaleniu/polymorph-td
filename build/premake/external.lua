
-- Graphics API.
newoption 
{
	trigger 	= "gfx-api",
	value		= "API",
	description = "Graphics API.",
	allowed 	= { {"opengl",	"OpenGL"} }
}
_OPTIONS["gfx-api"] = _OPTIONS["gfx-api"] or "opengl"

-- Extensions API.
newoption
{
	trigger		= "ext-api",
	value		= "API",
	description = "Extensions API.",
	allowed		= { {"boost", 	"Boost"} } -- Future C++11 implementations might depricate this.
}
_OPTIONS["ext-api"] = _OPTIONS["ext-api"] or "boost"

-- Math API.
newoption
{
	trigger		= "math-api",
	value		= "API",
	description	= "Math API.",
	allowed	= 
	{
		{"eigen", 	 "Eigen"},
		{"math_ext", "Custom Math Extension"} 
	}
}
_OPTIONS["math-api"] = _OPTIONS["math-api"] or "eigen"

-- Image loading API.
newoption
{
	trigger		= "il-api",
	value		= "API",
	description	= "Image loading API.",
	allowed		= { {"libpng",	"libPNG"} }
}
_OPTIONS["il-api"] = _OPTIONS["il-api"] or "libpng"

log("Graphics API")
log("  " .. _OPTIONS["gfx-api"])
log()
log("Extensions API")
log("  " .. _OPTIONS["ext-api"])
log()
log("Math API")
log("  " .. _OPTIONS["math-api"])
log()
log("Image loading API")
log("  " .. _OPTIONS["il-api"])
log()
--[[
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
							  includePath .. "boost",
							  includePath .. "boost/ext" }
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

function externalAPIs(api)
	local apiArr
	
	if type(api) == "string" then
		apiArr = { api }
	elseif type(api) == "table" then
		apiArr = api
	else
		assert(false, "Incorrect type of argument, type is " .. type(api))
	end
	
	for i, v in ipairs(apiArr) do
		local apiUse = externalAPI[v]
		
		assert(apiUse ~= nil, "Cannot find api " .. v)
		apiUse.use()
	end
end
--]]

