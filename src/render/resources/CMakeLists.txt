#######################
#### CONFIGURATION ####
#######################

#settings.h header file
#configure_file(
#"settings.h.in"
#"settings.h"
#)

########################
#### Subdirectories ####
########################

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/data")

#################
#### SOURCES ####
#################

#Add the appropriate source directories
set(APPLICATION_SOURCE_DIRS
${APPLICATION_SOURCE_DIRS}
"${CMAKE_CURRENT_SOURCE_DIR}"
PARENT_SCOPE
)

#Add the appropriate source files
set(APPLICATION_SOURCE_FILES
${APPLICATION_SOURCE_FILES}
"${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/material.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/shaderhook.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/bufferedmesh.cpp"
PARENT_SCOPE
)
