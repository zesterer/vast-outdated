#######################
#### CONFIGURATION ####
#######################

#settings.h header file
configure_file(
"config.h.in"
"config.h"
)

#################
#### SOURCES ####
#################

#Add the appropriate source directories
set(APPLICATION_SOURCE_DIRS
${APPLICATION_SOURCE_DIRS}
"${PROJECT_BINARY_DIR}/include"
PARENT_SCOPE
)
