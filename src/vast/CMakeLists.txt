########################
#### Subdirectories ####
########################

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/com")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sys")

#################
#### SOURCES ####
#################

#Add the appropriate source files
set(APPLICATION_SOURCE_FILES
${APPLICATION_SOURCE_FILES}
PARENT_SCOPE
)
