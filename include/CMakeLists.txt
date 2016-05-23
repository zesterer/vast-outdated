########################
#### Subdirectories ####
########################

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vast")

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
PARENT_SCOPE
)
