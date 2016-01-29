#########################################
## Place here all the {{ pluginName }} source files
#########################################

set({{ pluginName }}_SOURCES
   {{ pluginName }}.h
   {{ pluginName }}.cpp
   Configuration.h
   Configuration.cpp
)


#########################################
## Place here all additional include directories
## (by default yadoms-shared and boost are included)
#########################################
set({{ pluginName }}_ADDITIONAL_INC_DIR
)

#########################################
## Place here all additional libraries to link with
## (by default yadoms-shared and boost are included)
#########################################
set({{ pluginName }}_ADDITIONAL_LIB
)

#########################################
## Always leave this three lines to configure {{ pluginName }} correctly
## even if MAILSENDER_ADDITIONAL_INC_DIR or MAILSENDER_ADDITIONAL_LIB are empty
#########################################
PLUGIN_SOURCES({{ pluginName }} ${{ '{' }}{{ pluginName }}_SOURCES})
PLUGIN_INCLDIR({{ pluginName }} ${{ '{' }}{{ pluginName }}_ADDITIONAL_INC_DIR})
PLUGIN_LINK({{ pluginName }} ${{ '{' }}{{ pluginName }}_ADDITIONAL_LIB})

#########################################
## Post-build commands
## Copy files to build directory
## "package.json" and "icon.png" are needed, but you can add extra-files
#########################################
PLUGIN_POST_BUILD_COPY_FILE({{ pluginName }} package.json)
PLUGIN_POST_BUILD_COPY_FILE({{ pluginName }} icon.png)
PLUGIN_POST_BUILD_COPY_DIRECTORY({{ pluginName }} locales)

