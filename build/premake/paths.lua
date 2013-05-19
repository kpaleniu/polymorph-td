
--[[

Polymorph paths.
Using absolute paths since relative paths are relative to the
specific script being run.

]]--

-- Polymorph premake base file path.
premakePath		= os.getcwd() .. "/"

-- Root path.
projPath		= premakePath .. "../../"

-- Path to externals.
externalPath	= projPath .. "external/"


-------- MODULE PATHS -------

modulePath		= premakePath .. "modules/"
sourcePath		= projPath .. "src/"
includePath		= projPath .. "include/"

------------------------------

--------- TEST PATHS ---------

testSourcePath	= projPath .. "test/src/"
testIncludePath	= projPath .. "test/include/"

------------------------------

--------- TOOL PATHS ---------

toolSourcePath	= projPath .. "tool/src/"
toolIncludePath	= projPath .. "tool/include/"

------------------------------

-- Root path to addons.
addonPath		= projPath .. "addon/"
