## Main trunk of ewalena includes
include_directories (
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}
  )

## Subdirectories in the tests tree
add_subdirectory (matrix)
add_subdirectory (vector)

