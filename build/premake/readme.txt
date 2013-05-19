--- Build system documentation ---


-- Usage --

- Running premake -

From the directory 'build/premake' run:

premake4 <premake-options> premake-target solution <'verbose'>
	<premake-options>	See external.lua.
	premake-target		See premake4 documentation.
	solution			Path to solution to build (excluding '.lua').
	<'verbose'>			If verbose is added, logging from scripts occur.
	
Arguments in '<' '>' are optional.

For common premake commands, see 'build/premake/scripts'.


-- File system --

build/premake
	premake4.lua	
		Root premake script that generates the solution.
	
	base.lua
		Contains non-"build file creational" definitions used
		by all projects.
	
	external.lua
		Contains the premake options for the modules of Polymorph.
		This mostly concerns externals API usage.
	
build/premake/modules
	Holds definitions for all modules in Polymorph.
	
build/premake/tests/solutions
	Test solution definitions.
	
build/premake/scripts
	Executable scripts for running premake for certain solutions.
	
addon/<addon-name>/build/premake
	addon.lua
		Premake addon setup file. This is run before the main
		addon file.
	
addon/<addon-name>/build/premake/modules
	<addon-name>.lua
		Addon project definition.


-- Adding --

- Modules -

To add a module ("in-built project") to Polymorph, create a new 
file in 'build/premake/modules' that is named <project_name>.lua.
A module is a project that should be used in many projects.

The project file should contain one and only one project named
<project_name>. In module files, you should not use premake's:
'links', 'defines', 'includedirs', 'libdirs' unless
those commands should ONLY be used for that project and not 
for projects using the module. For proper dependency handling, use
'pm.links', 'pm.defines', 'pm.includedirs', 'pm.libdirs'; that 
way projects that include that project will also use those 
directives. 'pm.links' should be used to add external libraries,
for adding another project as a dependency to link use 
'pm.moduleDependencies' or 'pm.projectDependency'.

You can use 'files' to include files in a module, but it is better
to use 'pm.cppFiles'. Using 'pm.cppFiles' you'll get filters as well.
Usage is:

pm.cppFiles(sourcePath, 
			includePath=sourcePath, 
			inlinePath=includePath)

and the filters will reflect the current configuration.

- Solutions -

To add a solution, create a premake file that defines one and
only one solution. In the beginning of the solution body, add
'polymorphSolution()', this will create common configurations
and settings that should be used by all solutions. You should
not add modules directly to the solution, instead in the 
start-up project that you define in the solution, use
'pm.moduleDependencies' or similar. The needed projects will be
added automatically.

To create the solution, see beginning of this file.