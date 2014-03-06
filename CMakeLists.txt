## -------------------------------------------------------------------
## Copyright 2013 gubbins.
##
## Author: Toby D. Young
## -------------------------------------------------------------------

cmake_minimum_required (VERSION 2.8)

# ewalena
set (EWALENA_VERSION 0.3.0)
set (EWALENA_BASE_NAME ewalena)
set (EWALENA_INCLUDES "${CMAKE_SOURCE_DIR}/include")
set (EWALENA_LIBRARIES "${CMAKE_SOURCE_DIR}/lib")
set (CMAKE_BUILD_TYPE Debug)

message ("-- Setting up namespace ewalena (${EWALENA_BASE_NAME} ${EWALENA_VERSION})")

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

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
  ${CMAKE_SOURCE_DIR}/cmake
  ${CMAKE_SOURCE_DIR}/cmake/modules)

# initial cache
set (ELEMENTAL_DIR "" CACHE STRING "Hint to the elemental path")

# check_cxx_compiler_flag (-std=c++11 EWALENA_HAVE_FLAG_CXX11)
set (EWALENA_CXX_FLAGS "${EWALENA_CXX_FLAGS} -std=c++11")
set (EWALENA_CXX_FLAGS "${EWALENA_CXX_FLAGS} -rdynamic")
set (EWALENA_CXX_FLAGS "${EWALENA_CXX_FLAGS} -fPIC")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EWALENA_CXX_FLAGS}")

set (CMAKE_INCLUDE_CURRENT_DIR true)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# start project
project (EWALENA)
set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
add_subdirectory (source)

# Feature configuration:
find_package (Elemental) # optional
if (ELEMENTAL_FOUND)
  include_directories (${ELEMENTAL_INCLUDES})
endif (ELEMENTAL_FOUND)

# start testing
enable_testing () 
target_link_libraries (ewalena)
add_subdirectory (tests)





