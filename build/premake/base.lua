commandLine = {}

local indention = 0
local verbose = false
local commandLineUsage = [[
Usage:

premake4 <target> <solutionPath> (<logging>)
    target       - any valid premake target.
    solutionPath - path to premake file defining a solution.
    logging      - 'verbose' or nothing, if verbose logging 
                   from premake files is enabled.

Example:

premake4 vs2010 test/solutions/io verbose
]]

function log(msg)
	if not verbose then
		return
	end
	
	if msg then
		print(string.rep("  ", indention) .. msg)
	else
		print()
	end
end

function indent()
	indention = indention + 1
end

function unindent()
	indention = indention - 1
end

function listToString(tbl)
	local rStr = ""
	
	for i, str in ipairs(tbl) do
		rStr = rStr .. tostring(str) .. " "
	end
	
	return rStr
end

function parseCommandLine()
	assert(_ARGS[1], 
	       "\n\nMissing solution to create.\n" .. commandLineUsage)
	
	commandLine.solution = _ARGS[1]
	
	if _ARGS[2] and _ARGS[2] == "verbose" then
		verbose = true
	end
end