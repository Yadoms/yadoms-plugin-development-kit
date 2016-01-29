project (temp)

# Check the minimum CMake version
cmake_minimum_required (VERSION 3.2.0)

# First checks (compilers versions...)
include(../extern/cmake/preChecks.cmake)

include(tempConf.cmake)

# Windows specific macro
if(WIN32)
	include(../extern/cmake/windows.cmake)
endif()

# Compilers/IDE configurations
include(../extern/cmake/compilers.cmake)

# Boost built libraries copy helper
include(../extern/cmake/copyBoost.cmake)

##################################################################################################
## Project output configuration
##################################################################################################

#define outputs
set(outputDirectory ${PROJECT_SOURCE_DIR}/../builds)

# First for the generic no-config case (e.g. with gcc)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${outputDirectory} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${outputDirectory}/plugins )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${outputDirectory} )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${outputDirectory}/${OUTPUTCONFIG} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${outputDirectory}/${OUTPUTCONFIG}/plugins )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${outputDirectory}/${OUTPUTCONFIG} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )



##################################################################################################
## Externals libraries (Boost, Thread, RT) only linked with
##################################################################################################

# Boost (dynamic linking)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions( -DBOOST_WHATEVER_DYN_LINK )
add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )
add_definitions( -DBOOST_SPIRIT_THREADSAFE )

# define all needed boost libraries
set(BOOST_LIBS 
   atomic
	system 
	filesystem 
	thread 
	date_time 
	chrono 
	regex
)

find_package(Boost 1.60.0 EXACT REQUIRED COMPONENTS ${BOOST_LIBS} )
set(BOOST_INCL_DIR ${Boost_INCLUDE_DIR} ${BOOST_ROOT})

## Thread Library
FIND_PACKAGE(Threads)

## RT Library
if(UNIX AND NOT APPLE)
    set(RT_LIBRARY rt)
endif()


## IOKIT (needed for Mac)
if(APPLE)
	include(../extern/cmake/mac.cmake)
	
	if(NOT IOKIT_FOUND)
		message(SEND_ERROR "Unable to find the requested IOKit libraries")
	endif()

	if(NOT CARBON_FOUND)
		message(SEND_ERROR "Unable to find the requested Carbon libraries")
	endif()
	set(LIBS ${LIBS} ${IOKIT_LIBRARY} ${CARBON_LIBRARY})
endif()


###############################################
# OpenSSL
#
###############################################
FIND_PACKAGE(OpenSSL)

if(NOT ${OPENSSL_FOUND})
	message("Cannot find opensll, all plugins which requires SSL features will not be loaded")
   set(OPENSSL_INCLUDE_DIR "")
endif()




###############################################
# POCO
#
# POCO_LIBS : define all required poco libraries
###############################################

SET ( POCO_LIBS
	PocoFoundation
   PocoJSON
	PocoNet
	PocoUtil
   PocoXML
   PocoZip
)

#if openssl is found, just add ssl libraries (PocoCrypto and PocoNetSSL)
if(${OPENSSL_FOUND})
	SET ( POCO_LIBS
      ${POCO_LIBS}
      PocoCrypto
      PocoNetSSL
   )
endif()


set( POCO_REQUIRE_MINIMUM_VERSION "1.6.0")
include(../extern/cmake/FindPoco.cmake)

IF(NOT ${Poco_FOUND})
	message(FATAL_ERROR "Unable to find the requested POCO libraries")
ENDIF()

if(${OPENSSL_FOUND})
   list(FIND Poco_FOUND_LIBS_NAME PocoNetSSL PocoNetSSLFoundIndex)
   if( ${PocoNetSSLFoundIndex} GREATER -1)
      SET(PocoNetSSLFound true)
   endif()
endif()



#in case of OpenSSL use
IF(${PocoNetSSLFound})
   IF(WIN32)
      #add libeay32.dll and ssleay32.dll as dependencies
      IF(EXISTS "${OPENSSL_ROOT_DIR}/bin/libeay32.dll")
         SET(PocoNetSSLDepends "${OPENSSL_ROOT_DIR}/bin/libeay32.dll")
      ENDIF()
       
      IF(EXISTS "${OPENSSL_ROOT_DIR}/bin/ssleay32.dll")
         SET(PocoNetSSLDepends ${PocoNetSSLDepends} "${OPENSSL_ROOT_DIR}/bin/ssleay32.dll")
      ENDIF()
       
   ENDIF(WIN32)
ENDIF()

# define libraries to link with
set(LIBS ${LIBS} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${RT_LIBRARY} ${Poco_FOUND_LIBS})


set(SHARED_COMMON_INCL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../extern/include/shared)
set(SHARED_INCL_DIR ${SHARED_COMMON_INCL_DIR})
IF(WIN32)
	set(SHARED_INCL_DIR ${SHARED_INCL_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../extern/include/shared/windows)
ELSEIF(APPLE)
	set(SHARED_INCL_DIR ${SHARED_INCL_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../extern/include/shared/mac)
ELSE()
	set(SHARED_INCL_DIR ${SHARED_INCL_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../extern/include/shared/linux)
ENDIF()





include(../extern/cmake/PluginKit.cmake)

include(temp.cmake)


##################################################################################################
## Include directories
##################################################################################################
set(PLUGIN_INCL_DIR
	${CMAKE_CURRENT_SOURCE_DIR}
	${SHARED_INCL_DIR}
)

set(PLUGIN_ALL_INCL_DIR
	${PLUGIN_INCL_DIR} 
	${BOOST_INCL_DIR} 
	${OPENSSL_INCLUDE_DIR}
	${Poco_INCLUDE_DIRS}
)

set_property( TARGET temp PROPERTY INCLUDE_DIRECTORIES ${PLUGIN_ALL_INCL_DIR})

