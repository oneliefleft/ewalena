// -------------------------------------------------------------------
// Copyright 2012 namespace ewalena authors. All rights reserved.
//
// Author: Toby D. Young
// -------------------------------------------------------------------

#include <ewalena/lac/vector.h>
#include <ewalena/lac/matrix.h>


// Inverse.

unsigned int test ()
{
  ewalena::Matrix<double> matrix (1, 1);
  ewalena::Matrix<double> inv_matrix (1, 1);

  matrix.identity ();
  inv_matrix.invert (matrix);

  std::cout << " Matrix: ";
  for (unsigned int i=0; i<matrix.n_rows (); ++i)
    for (unsigned int j=0; j<matrix.n_cols (); ++j)
      {
	std::cout << matrix(i, j) << " ";
      }
  std::cout << std::endl;

  return 0;
}


int main ()
{
  try
    {
      unsigned int error test ();
      assert (error == 0);
    }

  catch (std::exception &exc)
    {
      std::cerr << std::endl << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Exception on processing: " << std::endl
                << exc.what() << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;

      return 1;
    }

  catch (...)
    {
      std::cerr << std::endl << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Unknown exception!" << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    };
}
