#######################
#### CONFIGURATION ####
#######################

#settings.h header file
configure_file(
"settings.h.in"
"settings.h"
)

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
"${PROJECT_BINARY_DIR}/src"
"${CMAKE_CURRENT_SOURCE_DIR}"
"${CMAKE_CURRENT_SOURCE_DIR}/.."
PARENT_SCOPE
)

#Add the appropriate source files
set(APPLICATION_SOURCE_FILES
${APPLICATION_SOURCE_FILES}
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
PARENT_SCOPE
)
