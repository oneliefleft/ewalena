## matrix
set (src
    00 01 02 
  )

link_directories (${EWALENA_LIBRARY_DIR})

foreach (test ${src})
  set (testname "matrix-${test}")
  add_test (${test} ${testname})
  add_executable (${testname} ${test})
  target_link_libraries (${testname} ${EWALENA_BASE_NAME})
endforeach ()
 
