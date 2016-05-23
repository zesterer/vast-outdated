########################
#### Subdirectories ####
########################

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/app")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/base")

#################
#### SOURCES ####
#################

#Add the appropriate source files
set(APPLICATION_SOURCE_FILES
${APPLICATION_SOURCE_FILES}
PARENT_SCOPE
)
