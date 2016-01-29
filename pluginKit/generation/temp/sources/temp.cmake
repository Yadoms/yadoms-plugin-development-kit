#########################################
## Place here all the temp source files
#########################################

set(temp_SOURCES
   temp.h
   temp.cpp
   Configuration.h
   Configuration.cpp
)


#########################################
## Place here all additional include directories
## (by default yadoms-shared and boost are included)
#########################################
set(temp_ADDITIONAL_INC_DIR
)

#########################################
## Place here all additional libraries to link with
## (by default yadoms-shared and boost are included)
#########################################
set(temp_ADDITIONAL_LIB
)

#########################################
## Always leave this three lines to configure temp correctly
## even if MAILSENDER_ADDITIONAL_INC_DIR or MAILSENDER_ADDITIONAL_LIB are empty
#########################################
PLUGIN_SOURCES(temp ${temp_SOURCES})
PLUGIN_INCLDIR(temp ${temp_ADDITIONAL_INC_DIR})
PLUGIN_LINK(temp ${temp_ADDITIONAL_LIB})

#########################################
## Post-build commands
## Copy files to build directory
## "package.json" and "icon.png" are needed, but you can add extra-files
#########################################
PLUGIN_POST_BUILD_COPY_FILE(temp package.json)
PLUGIN_POST_BUILD_COPY_FILE(temp icon.png)
PLUGIN_POST_BUILD_COPY_DIRECTORY(temp locales)

