##
## Copyright (C) 2014 by the ewalena authors.
##
## This file is part of the namespace ewalena library.
##
## Author: Toby D. Young
##
## Defines:
##
## M_FOUND        : found M
## M_INCLUDE_DIRS : path to M include directories
## M_LIBRARIES    : the libraries needed to use M
##
## ELEMENTAL_FOUND        : found ELEMENTAL
## ELEMENTAL_INCLUDE_DIRS : path to ELEMENTAL include directories
## ELEMENTAL_LIBRARIES    : the libraries needed to use ELEMENTAL
## ELEMENTAL_DEFINITIONS  : compiler flags needed to use ELEMENTAL
##
## Note: ELEMENTAL depends on M so we check for that here even though it
## would be better style to create a FindM macro (TODO).
##

include (FindPackageHandleStandardArgs)

find_path (ELEMENTAL_INCLUDES matrices.hpp
  PATHS ${ELEMENTAL_DIR}
  PATH_SUFFIXES include elemental include/elemental)

find_library (ELEMENTAL_LIBRARIES
  NAMES elemental libelemental
  PATHS ${ELEMENTAL_DIR}
  PATH_SUFFIXES lib64 lib)

find_package_handle_standard_args (ELEMENTAL
  REQUIRED_VARS ELEMENTAL_INCLUDES ELEMENTAL_LIBRARIES)

if (ELEMENTAL_LIBRARIES)
  set (ELEMENTAL_FOUND TRUE)
  set (EWALENA_WITH_ELEMENTAL ON)
  mark_as_advanced (ELEMENTAL_INCLUDES ELEMENTAL_LIBRARIES)
else ()
  set (ELEMENTAL_FOUND FALSE)
  set (EWALENA_WITH_ELEMENTAL OFF)
  set (ELEMENTAL_DIR "" CACHE STRING "Path to the ELEMENTAL directory")
endif ()
