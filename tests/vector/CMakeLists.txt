## matrix
set (src
    00 01 02 
  )

link_directories (${EWALENA_LIBRARY_DIR})

foreach (test ${src})
   add_test (${test} ${test})
   add_executable (${test} ${test})
   target_link_libraries (${test} ${EWALENA_BASE_NAME})
endforeach ()
 
