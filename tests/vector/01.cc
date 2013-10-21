// -------------------------------------------------------------------
// Copyright 2012 namespace ewalena authors. All rights reserved.
//
// Author: Toby D. Young
// -------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <cmath>
#include <ewalena/base/vector.h>

// Initialization with a list.

unsigned int test ()
{
  ewalena::Vector<double> vector {1.0, 1.1, 1.2, 1.3, 1.4};

  std::cout << " Vector: ";
  for (unsigned int i=0; i<vector.n_rows (); ++i)
    {
      std::cout << vector(i) << " ";
    }
  std::cout << std::endl;

  return 0;
}

int main ()
{
  unsigned int error = test ();
  assert (error == 0);

  return 0;
}



