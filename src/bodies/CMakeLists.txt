#######################
#### CONFIGURATION ####
#######################

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
PARENT_SCOPE
)

#Add the appropriate source files
set(APPLICATION_SOURCE_FILES
${APPLICATION_SOURCE_FILES}
${CMAKE_CURRENT_SOURCE_DIR}/planet.cpp
PARENT_SCOPE
)
