// -------------------------------------------------------------------
// Copyright 2012 namespace ewalena authors. All rights reserved.
//
// Author: Toby D. Young
// -------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <cmath>
#include <ewalena/base/vector.h>


// Operators.

unsigned int test ()
{
  ewalena::Vector<double> vector (3);
  for (unsigned int i=0; i<vector.n_rows (); ++i)
    vector(i) = double(i);

  ewalena::Vector<double> vector_copy (vector);
  assert (vector_copy == vector);
  
  // += and /= operators
  vector_copy += vector_copy;
  vector_copy /= 2;
  assert (vector_copy == vector);
  
  // -= and clear () operators
  vector_copy -= vector;
  vector.clear ();
  assert (vector_copy == vector);

  return 0;
}

int main ()
{
  unsigned int error test ();
  assert (error == 0);

  return 0;
}



