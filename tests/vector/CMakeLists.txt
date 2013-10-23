## vector
set (src
    00 01 02 
  )

foreach (test ${src})
   add_test ("vector/${test}" ${test})
#  target_link_libraries (${test} "${CMAKE_SOURCE_DIR}/lib")
#  target_link_libraries (${test} ${EWALENA_BASE_NAME}) 
endforeach ()

