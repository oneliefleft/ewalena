## -------------------------------------------------------------------
## Copyright 2013 gubbins.
##
## Author: Toby D. Young
## -------------------------------------------------------------------

cmake_minimum_required (VERSION 2.8)

# ewalena
set (EWALENA_VERSION 0.3.0)
set (EWALENA_BASE_NAME ewalena)
set (CMAKE_BUILD_TYPE Debug)

include (CheckFunctionExists)
include (CheckSymbolExists)
include (CheckCXXCompilerFlag)
include (CheckCXXSourceCompiles)
include (CheckCXXSourceRuns)
include (CheckIncludeFile)
include (CheckIncludeFiles)
include (CheckIncludeFileCXX)

include (FindPackageHandleStandardArgs)

enable_language (C)
enable_language (CXX)

#check_cxx_compiler_flag (-std=c++11 EWALENA_HAVE_FLAG_CXX11)
#set (${CMAKE_CXX_FLAGS})

set (EWALENA_CXX_FLAGS "${EWALENA_CXX_FLAGS} -std=c++11")
set (EWALENA_CXX_FLAGS "${EWALENA_CXX_FLAGS} -rdynamic")
set (EWALENA_CXX_FLAGS "${EWALENA_CXX_FLAGS} -fPIC")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EWALENA_CXX_FLAGS}" )

set (CMAKE_INCLUDE_CURRENT_DIR true)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set (EWALENA_WITH_LIBRARIES ${EWALENA_WITH_LIBRARIES})

# start project
project (EWALENA)

set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
add_subdirectory (source)





# Appendix

#if (CXX_COMPILER_FLAG_RDYNAMIC)
#  add_definitions ("-rdynamic")
#endif ()

#foreach (library ${EWALENA_WITH_LIBRARIES})
#  target_link_libraries (${EWALENA_BASE_NAME} ${library}) 
#  message (STATUS "Added library ${library}")
#endforeach ()

