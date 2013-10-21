// -------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE NAMEPSACE EWALENA AUTHORS ``AS
// IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// NAMESPACE EWALENA AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and
// documentation are those of the authors and should not be
// interpreted as representing official policies, either expressed or
// implied, of the namespace ewalena authors.
// -------------------------------------------------------------------

#include <cassert>
#include <cstring>
#include <complex>
#include <stdlib.h>
#include <iostream>

#ifndef __ewalena_matrix_h
#define __ewalena_matrix_h

#include <ewalena/base/tensor.h>

namespace ewalena
{
  
  template <int, int, typename> class Tensor;

  /**
   * A class that denotes a simple matrix with no special qualities,
   * ie. no special symmetries, data access, etc.
   * 
   * Matrices are in row-column format.
   *
   * @author Toby D. Young 2012.
   *
   * \ingroup lac
   */
  template <typename ValueType = double>
    class Matrix
    {
    public:
    
    /**
     * Constructor.
     */
    Matrix ();
    
    /**
     * Destructor.
     */
    ~Matrix ();
    
    /**
     * Initialize a matrix of size
     * <code>m</code>\f$\times\f$<code>n</code>.  By default, matrix
     * elements are set to zero otherwise if <code>zero=false</code>,
     * matrix elements are left in an unspecified state.
     */
    explicit Matrix (const unsigned int m, 
		     const unsigned int n,
		     const bool         zero = true);
    
    /**
     * Initialize a matrix of size equal to the first, and second,
     * integers of a pair.
     */
    Matrix (std::pair<const unsigned int, const unsigned int> mn_pair,
	    const bool                                        zero = true);
    
    /**
     * Initialize a matrix with a tensor <code>T</code> with a memory
     * copy.
     *
     * @note This initializer is provided for rank two tensors only -
     * while other ranks remain undefined.
     */
    template <int dim>
    Matrix (const class Tensor<dim, 2, ValueType> &T);  
    
    /**
     * Initialize a matrix with a vector basis <code>V</code> with a
     * memory copy.
     */
    /* Matrix (const class VectorBasis<ValueType> &V);   */
    
    /**
     * Initialize a matrix with another matrix <code>M</code> with a
     * memory copy.
     */
    Matrix (const Matrix& M);
    
    /**
     * Return the number of rows this matrix has.
     */
    unsigned int n_rows () const;
    
    /**
     * Return the number of columns this matrix has.
     */
    unsigned int n_cols () const;
    
    /**
     * Return the number of elements this matrix has.
     */
    unsigned int n_elements () const;
    
    /**
     * Reinitialise this matrix to size <code>m</code>,
     * <code>n</code>.
     */
    void reinit (const unsigned int m,
		 const unsigned int n,
		 const bool         zero = true);
    
    /**
     * Reinitialise the contents of this matrix.
     */
    void reinit ();
    
    /**
     * Read-write access to the (<code>i</code>, <code>j</code>)th
     * component of this matrix.
     */
    ValueType& operator () (const unsigned int i, 
			    const unsigned int j);
    
    /**
     * Read only access to the <code>i</code>th, <code>j</code>th
     * index of this matrix.
     */
    const ValueType& operator () (const unsigned int i, 
				  const unsigned int j) const;
    
    /**
     * Return the inverse of matrix \f$M\f$.
     */
    void invert (const Matrix<ValueType> &M);
    
    /**
     * Multiply two matrices together:
     * \f$M_{ij}=M_{(a)ik}M_{(b)kj}\f$.
     */
    void mult (const Matrix<ValueType> &M_a, 
	       const Matrix<ValueType> &M_b);
    
    /**
     * Transpose multiply two matrices togerher:
     * \f$M_{ij}=M_{(a)ki}M_{(b)kj}\f$.
     */
    void Tmult (const Matrix<ValueType> &M_a, 
		const Matrix<ValueType> &M_b);
    
    /**
     * Multiply transpose two matrices together:
     * \f$M_{ij}=M_{(a)ik}M_{(b)jk}\f$.
     */
    void multT (const Matrix<ValueType> &M_a, 
		const Matrix<ValueType> &M_b);
    
    /**
     * Make this matrix the identity matrix (all previous data is
     * overwritten).
     */
    void identity ();
    
    /**
     * Return the norm of this matrix.
     */
    ValueType norm ();
    
    /**
     * Inline addition operator. Add <code>M</code> to
     * <code>this</code> matrix.
     */
    void operator += (const Matrix<ValueType> &M);
    
    /**
     * Inline subtraction operator. Subtract <code>M</code> from
     * <code>this</code> matrix.
     */
    void operator -= (const Matrix<ValueType> &M);
    
    /**
     * Inline multiplication operator. Multiply every element in
     * <code>M</code> by a <code>scalar</code>.
     */
    void operator *= (const ValueType &scalar);
    
    /**
     * Inline division operator. Divide every element in
     * <code>M</code> by a <code>scalar</code>.
     */
    void operator /= (const ValueType &scalar);
    
    /**
     * Equal operator. This is equivalent to a copy.
     */
    void operator = (const Matrix<ValueType> &M);
    
    /**
     * Equivalence operator. Return true if <code>this</code> matrix
     * is an identical copy of the matrix <code>M</code>.
     */
    bool operator == (const Matrix<ValueType> &M) const;
    
    /**
     * Return <code>true</code> if this matrix is symmetric, otherwise
     * return false.
     */
    bool is_symmetric () const;
    
    /**
     * Output operator to stream.
     */
    friend std::ostream& operator << (std::ostream            &output, 
				      const Matrix<ValueType> &M)
    {
      for (unsigned int i=0; i<M.n_rows ()*M.n_cols (); ++i) 

	/* Try to pretty print */
	(M.data[i]<(ValueType) 0.)
	  ?
	  output << M.data[i] << " "
	  :
	  output << " " 
		 << M.data[i] << " ";
      
      return output; 
    }
    
    protected:
    
    /**
     * Read only access operator to the underlying C array structure
     * associated with this matrix.
     */
    inline
    const 
    ValueType* operator* () const
    {
      return (*this).data;
    }
    
    /**
     * Read-write access operator to the underlying C array structure
     * associated with this matrix.
     */
    inline
    ValueType* operator* () 
    {
      return (*this).data;
    }
    
    private:
    
    /**
     * Internal reference to this matrix
     * row-size, ie. the number of rows
     * this matrix has.
     */
    unsigned int __n_rows;
    
    /**
     * Internal reference to this matrix
     * column size, ie. the number of
     * columns this matrix has.
     */
    unsigned int __n_cols;
    
    /**
     * Internal object denoting this
     * matrix data.
     */
    ValueType* data;
    
    }; /* Matrix */
  
  /*-------------- Inline and Other Functions -----------------------*/
  
  template <typename ValueType>
    inline 
    const ValueType& 
    Matrix<ValueType>::operator () (const unsigned int i, 
				    const unsigned int j) const
    {
      assert (i<__n_rows);
      assert (j<__n_cols);
      
      /* return data[  index[0].begin () + i*index[0].increment () */
      /* 		    + */
      /* 		    n_rows*(index[1].begin () + j*index[1].increment ()) ]; */
      
      return data[__n_cols*i+j];
    }
  
  template <typename ValueType>
    inline 
    ValueType& 
    Matrix<ValueType>::operator () (const unsigned int i, 
				    const unsigned int j) 
    {
      assert (i<__n_rows);
      assert (j<__n_cols);
      
      return data[__n_cols*i+j];
    }

  template <typename ValueType>
    inline
    unsigned int
    Matrix<ValueType>::n_rows () const
    {
      return this->__n_rows;
    }
  
  template <typename ValueType>
    inline
    unsigned int
    Matrix<ValueType>::n_cols () const
    {
      return this->__n_cols;
    }

  template <typename ValueType>
    inline
    unsigned int
    Matrix<ValueType>::n_elements () const
    {
      return (this->__n_rows)*(this->__n_cols);
    }

  template <typename ValueType>
    inline 
    void
    Matrix<ValueType>::operator += (const Matrix<ValueType> &M) 
    {
      assert (M.__n_rows == this->__n_rows);
      assert (M.__n_cols == this->__n_cols);
      
      for (unsigned int i=0; i<__n_rows*__n_cols; ++i)
	data[i] += M.data[i];
    }

  template <typename ValueType>
    inline 
    void
    Matrix<ValueType>::operator -= (const Matrix<ValueType> &M) 
    {
      assert (M.__n_rows == this->__n_rows);
      assert (M.__n_cols == this->__n_cols);

      for (unsigned int i=0; i<__n_rows*__n_cols; ++i)
	data[i]  -= M.data[i];
    }

  template <typename ValueType>
    inline 
    void
    Matrix<ValueType>::operator *= (const ValueType &scalar) 
    {
      for (unsigned int i=0; i<__n_rows*__n_cols; ++i)
	data[i] *= scalar;
    }

  template <typename ValueType>
    inline 
    void
    Matrix<ValueType>::operator /= (const ValueType &scalar) 
    {
      for (unsigned int i=0; i<__n_rows*__n_cols; ++i)
	data[i] /= scalar;
    }

  template <typename ValueType>
    void
    Matrix<ValueType>::operator = (const Matrix<ValueType> &M) 
    {
      assert (M.data);

      assert (M.__n_rows == this->__n_rows);
      assert (M.__n_cols == this->__n_cols);

      for (unsigned int i=0; i<__n_rows; ++i) 
	for (unsigned int j=0; j<__n_cols; ++j) 
	  (*this)(i,j) = M(i,j);
    }

  template <typename ValueType>
    inline 
    bool
    Matrix<ValueType>::operator == (const Matrix<ValueType> &M) const
    {
      assert (M.__n_rows == this->__n_rows);
      assert (M.__n_cols == this->__n_cols);

      return static_cast<bool> (!std::memcmp (this->data, M.data, sizeof(ValueType)*(__n_rows*__n_cols)));
    }

  template <typename ValueType>
    inline 
    bool
    Matrix<ValueType>::is_symmetric () const
    {
      assert (this->data);
      assert (__n_rows == __n_cols);
      
      /* The matrix is trivially symmetric if it has zero size. */
      if (data)
	for (unsigned int i=0; i<__n_rows; ++i) 
	  for (unsigned int j=i+1; j<__n_cols; ++j) 
	    if ((*this)(i,j) != (*this)(j,i)) 
	      return false; 
      
      return true;
    }
  
  template <typename ValueType>
    inline 
    void
    Matrix<ValueType>::identity ()
    {
      /* An identity matrix is always a square matrix. */
      assert (this->__n_rows == this->__n_cols);
      this->reinit ();
      
      /* If the matrix is zero size - there is nothing to do. */
      if (__n_rows==0) 
	return;
      
      /* This is a cyclic counter that runs one past the length of a
	 column; ie. where 1 appears cyclicly in an identity
	 matrix. */
      unsigned int j = __n_rows+1;
      
      for (unsigned int i=0; i<(__n_rows*__n_cols); ++i, ++j)
	{
	  if (j==__n_rows+1) 
	    {
	      this->data[i] = ValueType(1);
	      j=0;
	    }
	}
    }
  
  template <typename ValueType>
    inline 
    ValueType
    Matrix<ValueType>::norm ()
    {
      assert (this->data);
      
      ValueType scalar = 0;
      
      for (unsigned int i=0; i<(this->__n_rows)*(this->__n_cols); ++i)
	scalar += std::fabs (this->data[i]);
      
      return scalar;
    }
  
  template <typename ValueType> 
    inline  
    void
    Matrix<ValueType>::mult (const Matrix<ValueType> &M_a, 
 			     const Matrix<ValueType> &M_b)  
    { 
      assert (M_a.data);
      assert (M_b.data);

      assert (M_a.__n_rows == M_b.__n_cols);  
      assert (M_a.__n_cols == M_b.__n_rows);  
      
      for (unsigned int i=0; i<M_a.__n_rows; ++i)
	for (unsigned int j=0; j<M_b.__n_cols; ++j)
	  for (unsigned int k=0; k<M_b.__n_rows; ++k)
	    (*this)(i,j) += M_a(i,k)*M_b(k,j);
    }

  template <typename ValueType> 
    inline  
    void
    Matrix<ValueType>::Tmult (const Matrix<ValueType> &M_a, 
			      const Matrix<ValueType> &M_b)  
    { 
      assert (M_a.data);
      assert (M_b.data);

      assert (M_a.__n_rows == M_b.__n_rows);  
      assert (M_a.__n_cols == M_b.__n_cols);  
      
      for (unsigned int i=0; i<M_a.__n_rows; ++i)
	for (unsigned int j=0; j<M_b.__n_cols; ++j)
	  for (unsigned int k=0; k<M_b.__n_rows; ++k)
	    (*this)(i,j) += M_a(k,i)*M_b(k,j);
    }

  template <typename ValueType> 
    inline  
    void
    Matrix<ValueType>::multT (const Matrix<ValueType> &M_a, 
			      const Matrix<ValueType> &M_b)  
    { 
      assert (M_a.data);
      assert (M_b.data);

      assert (M_a.__n_rows == M_b.__n_rows);  
      assert (M_a.__n_cols == M_b.__n_cols);  
      
      for (unsigned int i=0; i<M_a.__n_rows; ++i)
	for (unsigned int j=0; j<M_b.__n_cols; ++j)
	  for (unsigned int k=0; k<M_b.__n_rows; ++k)
	    (*this)(i,j) += M_a(i,k)*M_b(j,k);
    }

  /*-------------- Template and Other Functions ---------------------*/

  template <typename ValueType>
    template <int dim>
    Matrix<ValueType>::Matrix (const Tensor<dim, 2, ValueType> &T)
    {

      /* @todo: Generalise this for rank \neq 2. */
      __n_rows = dim;
      __n_cols = dim;
      data     = new ValueType[__n_rows*__n_cols];
      
      if ((__n_rows != 0) && (__n_cols !=0))
	std::memcpy (this->data, *T, sizeof(ValueType)*(__n_rows*__n_cols));
    }

  /* template <typename ValueType> */
  /*   Matrix<ValueType>::Matrix (const VectorBasis<ValueType> &V) */
  /*   { */
  /*     __n_rows = V.n_rows (); */
  /*     __n_cols = V.size (); */
  /*     data     = new ValueType[__n_rows*__n_cols]; */

  /*     if ((__n_rows != 0) && (__n_cols !=0)) */
  /* 	std::memcpy (this->data, *V, sizeof(ValueType)*(__n_rows*__n_cols)); */
  /*   } */

  template <typename ValueType>
    inline 
    void
    Matrix<ValueType>::invert (const Matrix<ValueType> &M)
    {
      assert (M.data);
      assert (M.__n_rows==M.__n_cols);

      this->reinit (M.__n_rows,M.__n_cols);

      switch (M.__n_cols)
	{
	case 0:
	  {
	    /* Undefined operation.  */
	    assert (false);
	  }

	case 1:
	  {
	    assert (M(0,0)!=ValueType (0));
	    (*this)(0,0) = ValueType (1) / M(0,0);
	    break;
	  }
	  
	case 2:
	  {
	    const ValueType determinant = M(0,0)*M(1,1) - M(0,1)*M(1,0);
	    assert (determinant!=ValueType (0));
	    
	    (*this)(0,0) =  M(1,1) / determinant;
	    (*this)(0,1) = -M(0,1) / determinant;
	    (*this)(1,0) = -M(1,0) / determinant;
	    (*this)(1,1) =  M(0,0) / determinant;
	    
	    break;
	  }

	case 3: 
	  {
	    const ValueType determinant 
	      = M(0,0)*(M(2,2)*M(1,1) - M(2,1)*M(1,2))
	      - M(1,0)*(M(2,2)*M(0,1) - M(2,1)*M(0,2))
	      + M(2,0)*(M(1,2)*M(0,1) - M(1,1)*M(0,2));
	    assert (determinant!=ValueType (0));

	    (*this)(0,0) =    (M(2,2)*M(1,1) - M(2,1)*M(1,2)) / determinant;
	    (*this)(0,1) =  - (M(2,2)*M(0,1) - M(2,1)*M(0,2)) / determinant;
	    (*this)(0,2) =    (M(1,2)*M(0,1) - M(1,1)*M(0,2)) / determinant;

	    (*this)(1,0) =  - (M(2,2)*M(1,0) - M(2,0)*M(1,2)) / determinant;
	    (*this)(1,1) =    (M(2,2)*M(0,0) - M(2,0)*M(0,2)) / determinant;
	    (*this)(1,2) =  - (M(1,2)*M(0,0) - M(1,0)*M(0,2)) / determinant;

	    (*this)(2,0) =    (M(2,1)*M(1,0) - M(2,0)*M(1,1)) / determinant;
	    (*this)(2,1) =  - (M(2,1)*M(0,0) - M(2,0)*M(0,1)) / determinant;
	    (*this)(2,2) =    (M(1,1)*M(0,0) - M(1,0)*M(0,1)) / determinant;

	    break; 

	  }

	  /* This is not likely to work well for big or even medium
	     sized matrices - so don't do it.  */
	default:
	  assert (false);
	}
      
    }
  
} /* namespace ewalena */

#endif /* __ewalena_matrix_h */
  
