########################
#### Subdirectories ####
########################

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/io")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/resource")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/util")

#################
#### SOURCES ####
#################

#Add the appropriate source files
set(APPLICATION_SOURCE_FILES
${APPLICATION_SOURCE_FILES}
PARENT_SCOPE
)
