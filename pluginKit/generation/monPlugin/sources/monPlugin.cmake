#########################################
## Place here all the monPlugin source files
#########################################

set(monPlugin_SOURCES
   monPlugin.h
   monPlugin.cpp
   Configuration.h
   Configuration.cpp
)


#########################################
## Place here all additional include directories
## (by default yadoms-shared and boost are included)
#########################################
set(monPlugin_ADDITIONAL_INC_DIR
)

#########################################
## Place here all additional libraries to link with
## (by default yadoms-shared and boost are included)
#########################################
set(monPlugin_ADDITIONAL_LIB
)

#########################################
## Always leave this three lines to configure monPlugin correctly
## even if MAILSENDER_ADDITIONAL_INC_DIR or MAILSENDER_ADDITIONAL_LIB are empty
#########################################
PLUGIN_SOURCES(monPlugin ${monPlugin_SOURCES})
PLUGIN_INCLDIR(monPlugin ${monPlugin_ADDITIONAL_INC_DIR})
PLUGIN_LINK(monPlugin ${monPlugin_ADDITIONAL_LIB})

#########################################
## Post-build commands
## Copy files to build directory
## "package.json" and "icon.png" are needed, but you can add extra-files
#########################################
PLUGIN_POST_BUILD_COPY_FILE(monPlugin package.json)
PLUGIN_POST_BUILD_COPY_FILE(monPlugin icon.png)
PLUGIN_POST_BUILD_COPY_DIRECTORY(monPlugin locales)

