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

# Add dependencies

#GLM - TODO
#dependencies += find_library('glm')

#SFML
dependencies += find_library('sfml-graphics')
dependencies += find_library('sfml-window')

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
)