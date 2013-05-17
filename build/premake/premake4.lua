
dofile("paths.lua")

dofile(premakePath .. "base.lua")
parseCommandLine()

log()


-- External library build options.

dofile(premakePath .. "external.lua")

--[[

[projectName] = 
{
	["projectDependencies"] = { ... },
	["configurations"] =
	{
		[configTerm]* =
		{
			["libdirs"] = { ... },
			["links"]	= { ... }, -- External libs only
			["libdirs"]	= { ... },
			["defines"] = { ... }
		}
	}
}

]]--

local projectMetaData = {}

log()

local function addProject(file)
	configuration "*"
	dofile(file)
	configuration "*"
end

local function modules(module)
	local moduleArr
	if type(module) == "string" then
		moduleArr = { module }
	elseif type(module) == "table" then
		moduleArr = module
	else
		assert(false, "Incorrect type of argument, type is " .. type(module))
	end
	
	local curProjName = project().name
	for i, m in ipairs(moduleArr) do
		addProject(modulePath .. module .. ".lua")
		
		project(curProjName)
	end
end

local function addons(addon)
	local addonArr
	if type(addon) == "string" then
		addonArr = { addon }
	elseif type(addon) == "table" then
		addonArr = addon
	else
		assert(false, "Incorrect type of argument, type is " .. type(addon))
	end
	
	for i, m in ipairs(addonArr) do
		dofile(addonPath .. addon .. "/build/premake/addon.lua")
		addProject(addonPath .. addon .. "/build/premake/modules/" .. addon .. ".lua")
	end
end

-- Adds value to the metadata key for this project and configuration.
local function addMetaData(key, value)
	local prj = project()
	local cnf = configuration()
	
	projectMetaData[prj.name] = 
		projectMetaData[prj.name] or {}
	
	projectMetaData[prj.name].config = 
		projectMetaData[prj.name].config or {}
		
	projectMetaData[prj.name].config[cnf.terms] =
		projectMetaData[prj.name].config[cnf.terms] or {}
	
	projectMetaData[prj.name].config[cnf.terms][key] =
		projectMetaData[prj.name].config[cnf.terms][key] or {}
	
	for i, v in ipairs(value) do
		table.insert(projectMetaData[prj.name].config[cnf.terms][key], v)
	end
end

local function alreadyInSolution(projName)
	local currentSolution = solution()
	
	for i, proj in ipairs(currentSolution.projects) do
		if projName == proj.name then
			return true
		end
	end
	
	return false
end

pm =
{
	moduleDependencies = function(projArr)
		local curProjName = project().name
		projectMetaData[curProjName] = 
			projectMetaData[curProjName] or {}
			
		projectMetaData[curProjName].dependentProjects = 
			projectMetaData[curProjName].dependentProjects or {}
		
		for _, v in ipairs(projArr) do
			table.insert(projectMetaData[curProjName].dependentProjects, v)
		end
		
		for _, projectName in ipairs(projArr) do
			if not alreadyInSolution(projectName) then
				modules(projectName)
			end
		end
	end,
	
	addonDependencies = function(addonArr)
		local curProjName = project().name
		projectMetaData[curProjName] = 
			projectMetaData[curProjName] or {}
			
		projectMetaData[curProjName].dependentProjects = 
			projectMetaData[curProjName].dependentProjects or {}
		
		for _, v in ipairs(addonArr) do
			table.insert(projectMetaData[curProjName].dependentProjects, v)
		end
		
		for _, projectName in ipairs(addonArr) do
			if not alreadyInSolution(projectName) then
				addons(projectName)
			end
		end
	end,
	
	projectDependency = function(path, proj)
		local curProjName = project().name
		projectMetaData[curProjName] = 
			projectMetaData[curProjName] or {}
			
		projectMetaData[curProjName].dependentProjects = 
			projectMetaData[curProjName].dependentProjects or {}
		
		table.insert(projectMetaData[curProjName].dependentProjects, proj)
		
		if not alreadyInSolution(proj) then
			addProject(path .. proj .. ".lua")
		end
	end,
	
	cppFiles = function(sourcePath, includePath, inlinePath)
		includePath = includePath or sourcePath
		inlinePath = inlinePath or includePath
		
		local cnfName = ""
		
		local cnf = configuration()
		if cnf and cnf.terms then
			for i, str in ipairs(cnf.terms) do
				cnfName = cnfName .. "/" .. str
			end
		end
		
		vpaths
		{
			["Headers" .. cnfName] = includePath .. "*.hpp",
			["Inlines" .. cnfName] = inlinePath  .. "*.inl",
			["Sources" .. cnfName] = sourcePath  .. "*.cpp",
		}
		
		files
		{
			includePath .. "*.hpp",
			inlinePath  .. "*.inl",
			sourcePath  .. "*.cpp",
		}
	end,
	
	includedirs = function(includeData)
		includedirs(includeData)
		
		addMetaData("includedirs", includeData)
	end,
	
	links = function(linkData)
		links(linkData)
		
		addMetaData("links", linkData)
	end,
	
	libdirs = function(libData)
		libdirs(libData)
		
		addMetaData("libdirs", libData)
	end,
	
	defines = function(defineData)
		defines(defineData)
		
		addMetaData("defines", defineData)
	end,
}

local function recursiveLinkDependencies(projMetaData_)
	local linked = {}
	
	function imp(projMetaData)
		if not projMetaData.dependentProjects then
			return
		end
		
		for i, dependentProjectName in ipairs(projMetaData.dependentProjects) do
			
			if not linked[dependentProjectName] then
				log("Linking " .. dependentProjectName)
				
				links(dependentProjectName)
				linked[dependentProjectName] = dependentProjectName
			end
			
			local dependentProjMetaData = 
				projectMetaData[dependentProjectName]
			
			if dependentProjMetaData 
			   and dependentProjMetaData.dependentProjects
			   and #dependentProjMetaData.dependentProjects > 0 then
				imp(dependentProjMetaData)
				--log("it: " .. dependentProjectName)
			end
		end
	end
	
	imp(projMetaData_)
end

local function recursiveAddConfigurations(projMetaData)

	if projMetaData.config then
		for cnfTerm, cnfData in pairs(projMetaData.config) do
			log(string.format("configuration '%s'", listToString(cnfTerm)))
			indent()
			
			configuration(cnfTerm)
				if cnfData.includedirs then
					log(string.format("includedirs '%s'", listToString(cnfData.includedirs)))
					includedirs(cnfData.includedirs)
				end
				if cnfData.links then
					log(string.format("links '%s'", listToString(cnfData.links)))
					links(cnfData.links)
				end
				if cnfData.libdirs then
					log(string.format("libdirs '%s'", listToString(cnfData.libdirs)))
					libdirs(cnfData.libdirs)
				end
				if cnfData.defines then
					log(string.format("defines '%s'", listToString(cnfData.defines)))
					defines(cnfData.defines)
				end
			
			unindent()
			log()
		end
	end
	
	if projMetaData.dependentProjects then
		for i, dependentProjectName in ipairs(projMetaData.dependentProjects) do
			local dependentProjMetaData = 
				projectMetaData[dependentProjectName]
			
			if dependentProjMetaData then
				recursiveAddConfigurations(dependentProjMetaData)
			end
		end
	end
end

local function printDependencies()
	log("Dependencies:")
	log()
	
	indent()
	for projName, projMetaData in pairs(projectMetaData) do
		log(string.format("'%s':", projName))
		indent()
		
		if projMetaData.dependentProjects then
			for _, dependProjName in ipairs(projMetaData.dependentProjects) do
				log(string.format("'%s'", dependProjName))
			end
		else
			log("No dependencies")
		end
		
		unindent()
	end
	unindent()
end

local function hasCyclicDependencies()
	
	local function imp(traversed, projName)
		if traversed[projName] then
			return true, projName
		end
		
		local metaData = projectMetaData[projName]
		if not metaData then
			return false
		end
		
		if not metaData.dependentProjects then
			return false
		end
		
		local traversedCopy = {}
		for k, v in pairs(traversed) do
			traversedCopy[k] = v
		end
		traversedCopy[projName] = projName
		
		for _, childName in ipairs(metaData.dependentProjects) do
			local rVal, proj = imp(traversedCopy, childName)
			if rVal then
				return true, proj
			end
		end
		
		return false
	end
	
	for projName, projMetaData in pairs(projectMetaData) do
		local rVal, proj = imp({}, projName)
		if rVal then
			return true, proj
		end
	end
	
	return false
end

local function handleDependencies()
	printDependencies()
	log()
	
	local rVal, proj = hasCyclicDependencies()
	assert(not rVal, 
		   "Cyclic dependencies detected for " .. tostring(proj))
	
	log()
	
	log("Binding dependencies.")
	log()
	indent()
	
	for projName, projMetaData in pairs(projectMetaData) do
		log("Handling project " .. projName)
		indent()
		
		project(projName)
			configuration {}
			
			log("Linking...")
			indent()
			
			recursiveLinkDependencies(projMetaData)
			
			unindent()
			log()
			
			log("Configure...")
			indent()
			
			recursiveAddConfigurations(projMetaData)
			
			unindent()
			log()
			
		unindent()
	end
	
	unindent()
end

function polymorphSolution()
	configuration {}

	configurations { "Debug", "Release" }
	platforms { "Native", "x64" }
	targetdir (projPath .. "bin/" .. solution().name)
	
	-- Generate own build directories for each target
	location ( projPath .. "build/" .. solution().name .. "/" .. _ACTION )
	objdir ( projPath .. "obj/" .. solution().name .. "/" .. _ACTION )
	
	includedirs { includePath .. "base" }
	
	-- C++0x/11 mode has to be explicitly enabled on some platforms
	configuration "not vs*"
		buildoptions { "-std=c++0x" }
		defines { "__GXX_EXPERIMENTAL_CXX0X__" }
	
	-- From 'configurations'
	configuration "Debug"
		flags { "Symbols", "ExtraWarnings" }
		defines { "_DEBUG" }
		libdirs { projPath .. "lib/Debug" }
	configuration "Release"
		flags { "Optimize" }
		defines { "NDEBUG" }
		libdirs { projPath .. "lib/Release" }
	
	configuration {}
end

log()

dofile(premakePath .. commandLine.solution .. ".lua")

handleDependencies()

log()