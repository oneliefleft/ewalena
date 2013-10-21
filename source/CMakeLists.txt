
## Main trunk of gubbins includes
include_directories (
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}
  )

## Subdirectoryies in the source tree
add_subdirectory (base)

## Wrap objects into a single library
add_library (${EWALENA_BASE_NAME} SHARED ## NB: this "SHARED" should not really be here!
  $<TARGET_OBJECTS:base>
)

## Set library properties
set_target_properties (${EWALENA_BASE_NAME} PROPERTIES SOVERSION ${EWALENA_VERSION})

## Link (with external) libraries
# target_link_libraries (${EWALENA_BASE_NAME} ${EWALENA_EXTERNAL_LIBRARIES})
