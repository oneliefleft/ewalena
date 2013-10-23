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
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <iostream>

#ifndef __ewalena_tensor_h
#define __ewalena_tensor_h

#include <ewalena/base/math.h>

namespace ewalena
{
  
  /**
   * A class that denotes a tensor with no special qualities, ie. no
   * special symmetries, data access, etc.
   *
   * @author Toby D. Young 2012.
   */
  template <int dim, int rank, typename ValueType = double>
    class Tensor
    {

    public:
    
    /**
     * Constructor.
     */
    Tensor (const bool zero = true);
    
    /**
     * Destructor.
     */
    ~Tensor ();
    
    /**
     * Initialize a tensor with another tensor <code>T</code> with a
     * memory copy.
     */
    Tensor (const Tensor &T);
    
    /**
     * Read-write access to the <code>i</code>th, <code>j</code>th,
     * etc. index of this tensor.
     */
    ValueType& operator () (const unsigned int index, ...);
    
    /**
     * Read only access to the <code>i</code>th, <code>j</code>th,
     * etc. index of this tensor.
     */
    const ValueType& operator () (const unsigned int index, ...) const;
    
    /**
     * Return the number of components this tensor has, ie. \f$d^r\f$.
     */
    unsigned int n_components () const;
    
    /**
     * Reinitialise the contents of this tensor to nothing (zero).
     */
    void reinit (); 
    
    /**
     * Clone the contents of \f$T\f$ tensor to <code>this</code>
     * tensor.
     */
    void clone (const Tensor<dim, rank, ValueType> &T);
    
    /**
     * Invert tensor \f$T\f$. @note This is instantiated for all rank
     * tensors, but will only work for rank two (everything else
     * triggers an exception).
     */
    void invert (const Tensor<dim, rank, ValueType> &T);
    
    /**
     * Sum-add a tensor to <code>this</code> tensor: \f$T+=aT_a\f$\,.
     */
    void sadd (const ValueType                    &a,
	       const Tensor<dim, rank, ValueType> &T_a);
    
    /**
     * Sum-add two tensors to <code>this</code> tensor:
     * \f$T+=aT_a+bT_b\f$\,.
     */
    void sadd (const ValueType                    &a,
	       const Tensor<dim, rank, ValueType> &T_a,
	       const ValueType                    &b,
	       const Tensor<dim, rank, ValueType> &T_b);
    
    /**
     * Sum-add three tensors to <code>this</code> tensor:
     * \f$T+=aT_a+bT_b\f$\,.
     */
    void sadd (const ValueType                    &a,
	       const Tensor<dim, rank, ValueType> &T_a,
	       const ValueType                    &b,
	       const Tensor<dim, rank, ValueType> &T_b,
	       const ValueType                    &c,
	       const Tensor<dim, rank, ValueType> &T_c);

    /**
     * Sum-add a vector of tensors to <code>this</code> tensor:
     * \f$T+=\sum_ia)iT_{a_i}\f$\,.
     */
    void sadd (const std::vector<ValueType>                     &a,
	       const std::vector<Tensor<dim, rank, ValueType> > &T_a);

    /**
     * Inline addition operator. Return <code>this</code> plus
     * <code>T</code> tensor.
     */
    Tensor<dim, rank, ValueType> operator + (const Tensor<dim, rank, ValueType> &T);

    /**
     * Inline subtraction operator. Return <code>this</code> minus
     * <code>T</code> tensor.
     */
    Tensor<dim, rank, ValueType> operator - (const Tensor<dim, rank, ValueType> &T);
    
    /**
     * Inline addition operator. Add <code>T</code> to
     * <code>this</code> tensor.
     */
    void operator += (const Tensor<dim, rank, ValueType> &T);
    
    /**
     * Inline subtraction operator. Subtract <code>T</code> from
     * <code>this</code> tensor.
     */
    void operator -= (const Tensor<dim, rank, ValueType> &T);
    
    /**
     * Inline multiplication operator. Multiply each element in
     * <code>this</code> tensor by a <code>scalar</code> value.
     */
    void operator *= (const ValueType &scalar);
    
    /**
     * Inline division operator. Divide each element in
     * <code>this</code> tensor by a <code>scalar</code> value.
     */
    void operator /= (const ValueType &scalar);
    
    /**
     * Equivalence operator. Return true if <code>this</code> tensor
     * is an identical copy of the tensor <code>T</code>.
     */
    bool operator == (const Tensor<dim, rank, ValueType> &T) const;
    
    /**
     * Return true if <code>this</code> tensor is symmetric.
     */
    bool is_symmetric () const;
    
    /**
     * Return the size of the Voight matrix representation of this
     * tensor.
     */
    std::pair<unsigned int, unsigned int> voight_components () const; 

    /**
     * Output operator to stream.
     */
    friend std::ostream& operator << (std::ostream                       &output, 
				      const Tensor<dim, rank, ValueType> &T)
    {
      for (unsigned int i=0; i<T.__n_components; ++i) 

	/* Try to pretty print */
	(T.data[i]<(ValueType) 0)
	  ?
	  output << T.data[i] << " "
	  :
	  output << " " 
		 << T.data[i] << " "; 
      
      return output; 
    }
    
    /**
     * Read-write access operator to the underlying C array structure
     * associated with this tensor field.
     */
    inline
    const 
    ValueType* operator* () const
    {
      return (*this).data;
    }
    
    /**
     * Read only access operator to the underlying C array structure
     * associated with this tensor field.
     */
    inline
    ValueType* operator* ()
    {
      return (*this).data;
    }
    
    protected:
    
    /**
     * Internal reference to the number of components this tensor has,
     * ie. \f$d^r\f$. (For internal reference this is just the length
     * of the underlying data array structure).
     */
    unsigned int __n_components;
    
    /**
     * Internal object storing the tensor dimension.
     */
    int __dim;
    
    /**
     * Internal object storing the tensor rank.
     */
    int __rank;
    
    private:
    
    /**
     * Internal object denoting this
     * tensor data.
     */
    ValueType *data;
    
    }; /* Tensor */
  
  /*-------------- Inline and Other Functions -----------------------*/
  
  template <int dim, int rank, typename ValueType>
    inline 
    ValueType& 
    Tensor<dim, rank, ValueType>::operator () (const unsigned int index, ...) 
    {
      /* Assert this object is initialised. */
      assert (__n_components != 0);
      assert (index < dim);
      
      /* Indices imply rank > zero. */
      unsigned int decimal = index;
      
      /* Initialise value list. */
      va_list index_list;
      va_start (index_list, index); 
      
      /* Count from one, as is done in base conversions, and to
	 prevent a compiler warning: comparison of unsigned expression
	 < 0 is always false. */
      for (unsigned int i=1; i<rank; ++i)  
	{
	  /* Read index from list and convert base_dim to base_10. */
	  unsigned int base_dim  = va_arg (index_list, unsigned int);
	  decimal               += static_cast<unsigned int> (math::pow (dim, i) * base_dim);
	  
	  assert (base_dim < dim);
	}
      
      /* Finalise value list. */
      va_end (index_list);
      
      /* Check that this index is in bounds. */
      assert (decimal < __n_components);
      return data[decimal];
    }
  
  /* This operator works in exactly the same way as the read-write
     operator above. Perhaps there is a way to simply call the above
     routine instead of duplicating that code? */
  template <int dim, int rank, typename ValueType>
    inline 
    const ValueType& 
    Tensor<dim, rank, ValueType>::operator () (const unsigned int index, ...) const
    {
      assert (__n_components != 0);
      assert (index < dim);
      
      unsigned int decimal = index;
      
      va_list index_list;
      va_start (index_list, index); 
      for (unsigned int i=1; i<rank; ++i) 
	{
	  unsigned int base_dim  = va_arg (index_list, unsigned int);
	  decimal               += static_cast<unsigned int> (math::pow (dim, i) * base_dim);
	  
	  assert (base_dim < dim);
	}
      va_end (index_list);

      assert (decimal < __n_components);
      return data[decimal];
    }

  template <int dim, int rank, typename ValueType>
    inline
    unsigned int
    Tensor<dim, rank, ValueType>::n_components () const
    {
      return __n_components;
    }

  template <int dim, int rank, typename ValueType>
    inline 
    Tensor<dim, rank, ValueType>
    Tensor<dim, rank, ValueType>::operator + (const Tensor<dim, rank, ValueType> &T) 
    {
      assert (__n_components != 0);
      assert (T.__n_components  == __n_components);

      Tensor<dim, rank, ValueType> tensor;
      tensor.reinit ();

      for (unsigned int i=0; i<__n_components; ++i)
	tensor.data[i] = data[i] + T.data[i];

      return tensor;
    }

  template <int dim, int rank, typename ValueType>
    inline 
    Tensor<dim, rank, ValueType>
    Tensor<dim, rank, ValueType>::operator - (const Tensor<dim, rank, ValueType> &T) 
    {
      assert (__n_components != 0);
      assert (T.__n_components  == __n_components);

      Tensor<dim, rank, ValueType> tensor;
      tensor.reinit ();

      for (unsigned int i=0; i<__n_components; ++i)
	tensor.data[i] = data[i] - T.data[i];

      return tensor;
    }
  
  template <int dim, int rank, typename ValueType>
    inline 
    void
    Tensor<dim, rank, ValueType>::operator += (const Tensor<dim, rank, ValueType> &T) 
    {
      assert (__n_components != 0);
      assert (T.__n_components  == __n_components);
      
      for (unsigned int i=0; i<__n_components; ++i)
	data[i] += T.data[i];
    }

  template <int dim, int rank, typename ValueType>
    inline 
    void
    Tensor<dim, rank, ValueType>::operator -= (const Tensor<dim, rank, ValueType> &T) 
    {
      assert (__n_components != 0);
      assert (T.__n_components  == __n_components);
      
      for (unsigned int i=0; i<__n_components; ++i)
	data[i] -= T.data[i];
    }
  
  template <int dim, int rank, typename ValueType>
    inline 
    void
    Tensor<dim, rank, ValueType>::operator *= (const ValueType &scalar) 
    {
      assert (__n_components != 0);

      for (unsigned int i=0; i<__n_components; ++i)
	data[i] *= scalar;
    }

  template <int dim, int rank, typename ValueType>
    inline 
    void
    Tensor<dim, rank, ValueType>::operator /= (const ValueType &scalar) 
    {
      assert (__n_components != 0);

      for (unsigned int i=0; i<__n_components; ++i)
	data[i] /= scalar;
    }

  template <int dim, int rank, typename ValueType>
    inline 
    bool
    Tensor<dim, rank, ValueType>::operator == (const Tensor<dim, rank, ValueType> &T) const
    {
      assert (T.__n_components == __n_components);

      return static_cast<bool> (!std::memcmp (this->data, T.data, sizeof(ValueType)*__n_components));
    }

  template <int dim, int rank, typename ValueType>
    inline
    void
    Tensor<dim, rank, ValueType>::sadd (const ValueType                    &a,
					const Tensor<dim, rank, ValueType> &T_a) 
    {
      /* Check this tensor is fo non-zero size and also check the
	 input tensors are also of the same size as that. */
      assert (__n_components != 0);
      assert (T_a.__n_components  == __n_components);

      /* Scale add these tensors thus: */
      for (unsigned int i=0; i<n_components (); ++i)
	this->data[i] += a*T_a.data[i];
    }
  
  template <int dim, int rank, typename ValueType>
    inline
    void
    Tensor<dim, rank, ValueType>::sadd (const ValueType                    &a,
					const Tensor<dim, rank, ValueType> &T_a,
					const ValueType                    &b,
					const Tensor<dim, rank, ValueType> &T_b) 
    {
      /* Same as above but for two tensors. */      
      assert (__n_components != 0);
      assert (T_a.__n_components  == __n_components);
      assert (T_b.__n_components  == __n_components);
      
      for (unsigned int i=0; i<n_components (); ++i)
	this->data[i] += a*T_a.data[i] + b*T_b.data[i];
    }

  template <int dim, int rank, typename ValueType>
    inline
    void
    Tensor<dim, rank, ValueType>::sadd (const ValueType                    &a,
					const Tensor<dim, rank, ValueType> &T_a,
					const ValueType                    &b,
					const Tensor<dim, rank, ValueType> &T_b,
					const ValueType                    &c,
					const Tensor<dim, rank, ValueType> &T_c) 
    {
      /* Same as above but for two tensors. */
      assert (__n_components != 0);
      assert (T_a.__n_components  == __n_components);
      assert (T_b.__n_components  == __n_components);
      assert (T_c.__n_components  == __n_components);

      for (unsigned int i=0; i<n_components (); ++i)
	this->data[i] += a*T_a.data[i] + b*T_b.data[i] + c*T_c.data[i];
    }

  template <int dim, int rank, typename ValueType>
    inline
    void
    Tensor<dim, rank, ValueType>::sadd (const std::vector<ValueType>                     &a,
					const std::vector<Tensor<dim, rank, ValueType> > &T_a) 
    {
      /* Same as above but for a std::vector of tensors. */
      assert (__n_components != 0);

      /* Insist that the number of constants and the number of tensors
	 to scale-add are of the same size. */
      assert (T_a.size ()  == a.size ());

      for (unsigned int i=0; i<a.size (); ++i)
	{
	  assert (__n_components != 0);
	  assert (T_a[i].__n_components  == __n_components);

	  /* Iteratively call the single scale-add (above). */
	  this->sadd (a[i], T_a[i]);
	}
    }

  /*-------------- Rank 2 --------------------------------------------*/

  /* This routine is a definiative plagarism from the class
     Matrix<ValueType>. Thus, if anything goes wrong here, it will
     probably need to be reported there too. */
  template <int dim, int rank, typename ValueType>
    inline
    void
    Tensor<dim, rank, ValueType>::invert (const Tensor<dim, rank, ValueType> &T) 
    {
      /* This should always be true  */
      assert (dim < 4);
      assert (rank == 2);

      assert (T.data);
      assert ((*this).data);

      switch (dim)
	{
	case 0:
	  {
	    /* Undefined operation.  */
	    assert (false);
	  }
	  
	case 1:
	  {
	    assert (T(0,0)!=ValueType (0));
	    (*this)(0,0) = ValueType (1) / T(0,0);
	    break;
	  }
	  
	case 2:
	  {
	    const ValueType determinant = T(0,0)*T(1,1) - T(0,1)*T(1,0);
	    assert (determinant!=ValueType (0));
	    
	    (*this)(0,0) =  T(1,1) / determinant;
	    (*this)(0,1) = -T(0,1) / determinant;
	    (*this)(1,0) = -T(1,0) / determinant;
	    (*this)(1,1) =  T(0,0) / determinant;
	    
	    break;
	  }

	case 3: 
	  {
	    const ValueType determinant 
	      = T(0,0)*(T(2,2)*T(1,1) - T(2,1)*T(1,2))
	      - T(1,0)*(T(2,2)*T(0,1) - T(2,1)*T(0,2))
	      + T(2,0)*(T(1,2)*T(0,1) - T(1,1)*T(0,2));
	    assert (determinant!=ValueType (0));

	    (*this)(0,0) =    (T(2,2)*T(1,1) - T(2,1)*T(1,2)) / determinant;
	    (*this)(0,1) =  - (T(2,2)*T(0,1) - T(2,1)*T(0,2)) / determinant;
	    (*this)(0,2) =    (T(1,2)*T(0,1) - T(1,1)*T(0,2)) / determinant;

	    (*this)(1,0) =  - (T(2,2)*T(1,0) - T(2,0)*T(1,2)) / determinant;
	    (*this)(1,1) =    (T(2,2)*T(0,0) - T(2,0)*T(0,2)) / determinant;
	    (*this)(1,2) =  - (T(1,2)*T(0,0) - T(1,0)*T(0,2)) / determinant;

	    (*this)(2,0) =    (T(2,1)*T(1,0) - T(2,0)*T(1,1)) / determinant;
	    (*this)(2,1) =  - (T(2,1)*T(0,0) - T(2,0)*T(0,1)) / determinant;
	    (*this)(2,2) =    (T(1,1)*T(0,0) - T(1,0)*T(0,1)) / determinant;

	    break; 

	  }

	  /* This is not likely to work well for big or even medium
	     sized matrices - so don't do it. */
	default:
	  assert (false);
	}

    }

  /*-------------- Rank 2 --------------------------------------------*/

  /**
   * Contract two normal ordered tenors
   * \f$T_{kl}=T_{(a)ij}T_{(b)ijkl}\f$.
   */
  template <int dim, typename ValueType>
    inline
    Tensor<dim, 2, ValueType> contract (const Tensor<dim, 2, ValueType> &T_a,
					const Tensor<dim, 4, ValueType> &T_b) 
    {
      Tensor<dim, 2, ValueType> tensor;
      
      for (unsigned int i=0; i<dim; ++i)
	for (unsigned int j=0; j<dim; ++j)
	  for (unsigned int k=0; k<dim; ++k)
	    for (unsigned int l=0; l<dim; ++l)
	      tensor(k,l) += T_a(i,j)*T_b(i,j,k,l);
      
      return tensor;
    }
  
  /**
   * Contract two normal ordered tenors
   * \f$T_{ij}=T_{(a)ijkl}T_{(b)kl}\f$.
   */
  template <int dim, typename ValueType>
    inline
    Tensor<dim, 2, ValueType> contract (const Tensor<dim, 4, ValueType> &T_a,
					const Tensor<dim, 2, ValueType> &T_b) 
    {
      Tensor<dim, 2, ValueType> tensor;
      
      for (unsigned int i=0; i<dim; ++i)
	for (unsigned int j=0; j<dim; ++j)
	  for (unsigned int k=0; k<dim; ++k)
	    for (unsigned int l=0; l<dim; ++l)
	      tensor(i,j) += T_a(i,j,k,l)*T_b(k,l);
      
      return tensor;
    }
  
  /*-------------- Rank 1 --------------------------------------------*/
  
  /**
   * Contract two normal ordered tenors
   * \f$T_{i}=T_{(a)ijk}T_{(b)jk}\f$.
   */
  template <int dim, typename ValueType>
    inline
    Tensor<dim, 1, ValueType> contract (const Tensor<dim, 3, ValueType> &T_a,
					const Tensor<dim, 2, ValueType> &T_b) 
    {
      Tensor<dim, 1, ValueType> tensor;
      
      for (unsigned int i=0; i<dim; ++i)
	for (unsigned int j=0; j<dim; ++j)
	  for (unsigned int k=0; k<dim; ++k)
	    tensor(i) += T_a(i,j,k)*T_b(j,k);
      
      return tensor;
    }
  
  /*-------------- Scalar --------------------------------------------*/

  
} /* namespace ewalena */
  
#endif /* __ewalena_tensor_h */
  
