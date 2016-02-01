# Set up the project

project(
'vast',
'cpp',
version : '0.0.0',
license : 'GPL-2.0',
)

# Set up initial variables

binary_name = 'vast'

isgui = true
datadir = 'data'

includes = []
dependencies = []
sources = []
linklibs = []
compileflags = []
compileflags += '--std=c++11'

# Add dependencies

#GLM - Kind of hackish, but it works (GLM is header-only, so this is necessary)
compiler = meson.get_compiler('cpp')
#if compiler.has_header('glm/glm.hpp')
#	message('Found GLM')
#else
#	error('Cannot find GLM')
#endif

#SFML
dependencies += dependency('sfml-graphics')
dependencies += dependency('sfml-window')

#GlBinding
dependencies += find_library('glbinding')

# Probe subdirectories

subdir('src')

# Copy the data directory to the build directory

run_command('cp', '-r', meson.source_root() + '/' + datadir, meson.build_root())

# Compile a binary

binary = executable(
binary_name,
sources,
include_directories : includes,
link_with : linklibs,
gui_app : isgui,
cpp_args : compileflags,
)