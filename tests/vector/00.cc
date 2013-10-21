// -------------------------------------------------------------------
// Copyright 2012 namespace ewalena authors. All rights reserved.
//
// Author: Toby D. Young
// -------------------------------------------------------------------

#include <iostream>
#include <cstring>
#include <cmath>
#include <ewalena/base/vector.h>

// Initialization and reinitialization.

unsigned int test ()
{
  // Initialise vector
  ewalena::Vector<double> vector (4);

  for (unsigned int i=0; i<vector.n_rows (); ++i)
    vector(i) = double(i);
  std::cout << " Vector: ";
  for (unsigned int i=0; i<vector.n_rows (); ++i)
    {
      std::cout << vector(i) << " ";
      assert (vector(i) == double(i));
    }
  std::cout << std::endl;

  // Reinitialize vector.
  vector.reinit (2);
  std::cout << " Vector: ";
  for (unsigned int i=0; i<vector.n_rows (); ++i)
    {
      std::cout << vector(i) << " ";
      assert (vector(i) == double(0));
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



