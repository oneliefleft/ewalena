// -------------------------------------------------------------------
// Copyright 2012 namespace ewalena authors. All rights reserved.
//
// Author: Toby D. Young
// -------------------------------------------------------------------

#include <ewalena/base/vector.h>
#include <ewalena/base/matrix.h>

// Operators.
unsigned int test ()
{
  ewalena::Matrix<double> left_matrix (3, 3);
  ewalena::Matrix<double> right_matrix (3, 3);
  
  left_matrix (0,0) = 1;
  left_matrix (0,1) = 1;
  left_matrix (0,2) = 1;
  left_matrix (1,0) = 1;
  left_matrix (1,1) = 1;
  left_matrix (1,2) = 1;
  left_matrix (2,0) = 1;
  left_matrix (2,1) = 1;
  left_matrix (2,2) = 1;

  right_matrix.identity ();
  right_matrix -= left_matrix;

  std::cout << "Sum of two matrices: " << std::endl;
  for (unsigned int i=0; i<right_matrix.n_rows (); ++i)
    for (unsigned int j=0; j<right_matrix.n_cols (); ++j)
      {
	std::cout << right_matrix(i,j) << " ";
	if (i != j)
	  assert (right_matrix(i,j) == double(-1));
      }
  std::cout << std::endl;

  // Get the diagonal of the right matrix
  ewalena::Vector<double> right_diagonal_vector (right_matrix.n_rows ());
  right_diagonal_vector.diag (right_matrix);
  
  // and then see if that is empty.
  ewalena::Vector<double> empty_vector (right_diagonal_vector.n_rows (), true);
  assert (right_diagonal_vector == empty_vector);

  return 0;
}

int main ()
{
  unsigned int error test ();
  assert (error == 0);

  return 0;
}
