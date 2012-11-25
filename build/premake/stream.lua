
--
-- I/O Stream project.
--
--[[
project "stream"
	kind "StaticLib"
	language "C++"
	
	files { projPath .. "/src/base/stream/**.cpp" }
	includedirs { projPath .. "/include/base" }
--]]