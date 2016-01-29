# Macros for setting up a plugin
#

MACRO(PLUGIN_SOURCES _targetName)
   set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${outputDirectory}/plugins/${_targetName} )
   foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
       string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
       set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${outputDirectory}/${OUTPUTCONFIG}/plugins/${_targetName} )
   endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
	add_library(${_targetName} MODULE ${ARGN})
ENDMACRO()

MACRO(PLUGIN_INCLDIR _targetName)

   #define the list of all include dirs
   set(PLUGINS_ALL_INCLUDE_DIRS ${SHARED_INCL_DIR} ${BOOST_INCL_DIR}  ${Poco_INCLUDE_DIRS} ${ARGN})
   #in case of OpenSSL found, just add openssl include dir
   if(${OPENSSL_FOUND})
      set(PLUGINS_ALL_INCLUDE_DIRS  ${PLUGINS_ALL_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
   endif()

	set_property( TARGET ${_targetName} PROPERTY INCLUDE_DIRECTORIES ${PLUGINS_ALL_INCLUDE_DIRS})
ENDMACRO()

MACRO(PLUGIN_LINK _targetName)
   set(YADOMS_SHARED_LIB_PATH)

   if(MSVC14)
      set(YADOMS_SHARED_LIB_PATH ../extern/lib/MSVC14/yadoms-shared)
   elseif(MSVC12)
      set(YADOMS_SHARED_LIB_PATH ../extern/lib/MSVC12/yadoms-shared)
   endif()
	
   target_link_libraries(${_targetName} ${YADOMS_SHARED_LIB_PATH} ${LIBS} ${CMAKE_DL_LIBS} ${ARGN})
   
   #configure plugin as installable component
	install(TARGETS ${_targetName} 
		LIBRARY DESTINATION ${INSTALL_BINDIR}/plugins/${_targetName}
		COMPONENT  ${_targetName})
ENDMACRO()

# brief Copy a file to the target output dir
# param [in] _targetName The current target (ie: pluginName)
# param [in] _resource The resource (absolute path) to copy to the target output dir
MACRO(PLUGIN_POST_BUILD_COPY_FILE _targetName _resource)

   get_filename_component(_resourcePath ${_resource}  DIRECTORY)
   
   install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${_resource} 
			DESTINATION ${INSTALL_BINDIR}/plugins/${_targetName}/${_resourcePath}
			COMPONENT  ${_targetName})
			
   add_custom_command(TARGET ${_targetName} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${_resource} $<TARGET_FILE_DIR:${_targetName}>/${_resource})
   if(COTIRE_USE)
      if(COTIRE_USE_UNITY)
         add_custom_command(TARGET ${_targetName}_unity POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/${_resource} $<TARGET_FILE_DIR:${_targetName}_unity>/${_resource})
	  endif()	
   endif()	
ENDMACRO()



# brief Copy a dependency (dll or so) to yadoms output dir (not next to _targetName)
# param [in] _targetName The current target (ie: pluginName)
# param [in] _resource The resource (absolute path) to copy to Yadoms dir
MACRO(PLUGIN_POST_BUILD_COPY_FILE_DEPENDENCY _targetName _resource)
   get_filename_component(_resourcePath ${_resource}  DIRECTORY)
   
   install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${_resource} 
			DESTINATION ${_resourcePath}
			COMPONENT  ${_targetName})
			
   add_custom_command(TARGET ${_targetName} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_resource} $<TARGET_FILE_DIR:yadoms>/)
   if(COTIRE_USE)
      if(COTIRE_USE_UNITY)
         add_custom_command(TARGET ${_targetName}_unity POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_resource} $<TARGET_FILE_DIR:yadoms_unity>/)
	  endif()	
   endif()	
ENDMACRO()

# brief Copy list of dependencies (dll or so) to yadoms output dir (not next to _targetName)
# param [in] _targetName The current target (ie: pluginName)
# param [in] _resources The resources (absolute path) to copy to Yadoms dir
MACRO(PLUGIN_POST_BUILD_COPY_FILE_DEPENDENCIES _targetName _resources)
   foreach(resource ${_resources})
      PLUGIN_POST_BUILD_COPY_FILE_DEPENDENCY(${_targetName} ${resource})
   endforeach(resource)
ENDMACRO()

# brief Copy a directory (and its content) to the target output dir
# param [in] _targetName The current target (ie: pluginName)
# param [in] _resource The resource folder (absolute path) to copy to the target output dir
MACRO(PLUGIN_POST_BUILD_COPY_DIRECTORY _targetName _resource)
   install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_resource} 
			DESTINATION ${INSTALL_BINDIR}/plugins/${_targetName}
			COMPONENT  ${_targetName})

   add_custom_command(TARGET ${_targetName} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${_resource} $<TARGET_FILE_DIR:${_targetName}>/${_resource})
	  
   if(COTIRE_USE)
      if(COTIRE_USE_UNITY)
         add_custom_command(TARGET ${_targetName}_unity POST_BUILD
           COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${_resource} $<TARGET_FILE_DIR:${_targetName}_unity>/${_resource})
	  endif()	
   endif()		  
ENDMACRO()
