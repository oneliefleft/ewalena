// -------------------------------------------------------------------
// Copyright 2012 namespace ewalena authors. All rights reserved.
//
// Author: Toby D. Young
// -------------------------------------------------------------------

#include <ewalena/lac/vector.h>
#include <ewalena/lac/matrix.h>

// Initialization and reinitialization.
unsigned int test ()
{
  // Initialise Matrix.
  ewalena::Matrix<double> matrix (4, 4);

  for (unsigned int i=0; i<matrix.n_rows (); ++i)
    for (unsigned int j=0; j<matrix.n_cols (); ++j)
      matrix(i, j) = double(i+j);

  std::cout << " Matrix: ";
  for (unsigned int i=0; i<matrix.n_rows (); ++i)
    for (unsigned int j=0; j<matrix.n_cols (); ++j)
      {
	std::cout << matrix(i, j) << " ";
	assert (matrix(i, j) == double(i+j));
      }
  std::cout << std::endl;

  // Reinitialize Matrix.
  matrix.reinit (4, 4, true);
  std::cout << " Matrix: ";
  for (unsigned int i=0; i<matrix.n_rows (); ++i)
    for (unsigned int j=0; j<matrix.n_cols (); ++j)
      std::cout << matrix(i, j) << " ";
  std::cout << std::endl;

  for (unsigned int i=0; i<matrix.n_rows (); ++i)
    for (unsigned int j=0; j<matrix.n_cols (); ++j)
      assert (matrix (i,j) == double(0));

  return 0;
}


int main ()
{
  unsigned int error test ();
  assert (error == 0);

  return 0;
}
