
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
	
	allowed	= 
	{
		{"boost", 	"Boost"},  -- Future C++11 implementations might depricate this.
		{"std", 	"Standard C++11"}
	}
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