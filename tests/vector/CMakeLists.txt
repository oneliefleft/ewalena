## vector
set (src
    00 01 02 
  )

foreach (test ${src})
   add_test (${test}, ${test})
   add_executable (${test} ${test})
endforeach ()
