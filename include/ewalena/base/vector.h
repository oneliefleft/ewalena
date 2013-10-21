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
#include <cmath>
#include <complex>
#include <cstring>
#include <iostream>

#ifndef __ewalena_vector_h
#define __ewalena_vector_h

#include <ewalena/base/matrix.h>

namespace ewalena
{
  
  /**
   * A class that denotes a simple vector with no special qualities,
   * ie. no special data access, etc.
   *
   * @author Toby D. Young 2012.
   */
  template <typename ValueType = double>
    class Vector
    {
    public:
    
    /**
     * Constructor - a vector of zero dimension.
     */
    Vector ();
    
    /**
     * Destructor.
     */
    ~Vector ();
    
    /**
     * Initialize a vector to size <code>m</code>.  Vector elements
     * are set to zero by default, and otherwise if
     * <code>zero=false</code>, vector elements are left in an
     * unspecified state.
     */
    explicit Vector (const unsigned int m,
		     const bool         zero = true);
    
    /**
     * Initialize a vector with another vector <code>v</code> with a
     * memory copy.
     */
    Vector (const Vector<ValueType> &v);
    
    /**
     * Initialize a vector with list <code>v</code> using a direct
     * memory copy. The length of <code>this</code> vector after
     * initialization will be equal to the length of the list
     * <code>v</code>;
     *
     * @note A typical usage of this could be:
     * <code>ewalena::Vector<double> V = {1.0, 1.1, 1.25}</code>.
     */
    Vector (std::initializer_list<ValueType> list);
    
    /**
     * Reinitialise the contents of this vector to nothing (zero).
     */
    void reinit ();
    
    /**
     * Return the size of this vector (number of rows).
     */
    unsigned int size () const;
    
    /**
     * Reinitialise this vector to size <code>m</code>.
     */
    void reinit (const unsigned int m,
		 const bool         zero = true);
    
    /**
     * Return the \f$\ell_1\f$-norm of this vector.
     */
    ValueType l1_norm ();
    
    /**
     * Return the \f$\ell_2\f$-norm of this vector.
     */
    ValueType l2_norm ();
    
    /**
     * Return the \f$\ell_p\f$-norm of this vector, where
     * \f$p\in{\mathbb Z}^+\f$.
     */
    ValueType lp_norm (unsigned int p);
    
    /**
     * Normalise this vector by the \f$\ell_2\f$-norm.
     */
    void l2_normalize ();
    
    /**
     * Normalise this vector by the \f$\ell_p\f$-norm, where
     * \f$p\in{\mathbb Z}^+\f$.
     */
    void lp_normalize (const unsigned int p);
    
    /**
     * Read-write access to the <code>i</code>th index of this vector.
     */
    ValueType& operator () (const unsigned int i);
    
    /**
     * Read only access to the <code>i</code>th index of this vector.
     */
    const ValueType& operator () (const unsigned int i) const;
    
    /**
     * Copy/equality operator. Make <code>this</code> vector equal to
     * <code>v</code>. All data in <code>this</code> is overwritten,
     * and its size is changed if needed.
     */
    void operator = (const Vector<ValueType> &v);
    
    /**
     * Inline addition operator. Add <code>v</code> to
     * <code>this</code> vector.
     */
    void operator += (const Vector<ValueType> &v);
    
    /**
     * Inline subtraction operator. Subtract <code>v</code> from
     * <code>this</code> vector.
     */
    void operator -= (const Vector<ValueType> &v);
    
    /**
     * Inline multiplication operator.  Multiply each component of
     * <code>this</code> vector by a <code>scalar</code>.
     */
    void operator *= (const ValueType &scalar);
    
    /**
     * Inline division operator.  Divide each component of
     * <code>this</code> vector by a <code>scalar</code>.
     */
    void operator /= (const ValueType &scalar);
    
    /**
     * Equivalence operator. Return true if <code>this</code> vector
     * is an identical copy of the vector <code>v</code>.
     */
    bool operator == (const Vector<ValueType> &v) const;
    
    /**
     * Output operator to stream.
     */
    friend std::ostream& operator << (std::ostream& output, 
				      const Vector<ValueType> &v)
    {
      for (unsigned int i=0; i<v.n_el; ++i) 

	/* Try to pretty print */
	(v.data[i]<(ValueType) 0)
	  ?
	  output << v.data[i] << " "
	  :
	  output << " " 
		 << v.data[i] << " "; 
      
      return output; 
    }
    
    
    /**
     * Return the size of this vector.
     */
    unsigned int n_rows () const;
    
    /**
     * Return the diagonal of a matrix as this vector.
     */
    void diag (const Matrix<ValueType> &M); 
    
    /**
     * Scale-and-add. Return <code>this = a*v</code>;
     */
    void sadd (const ValueType          a,
	       const Vector<ValueType> &v); 
    
    /**
     * Scale-and-add. Return <code>this = a*v + b*w</code>;
     */
    void sadd (const ValueType          a,
	       const Vector<ValueType> &v,
	       const ValueType          b,
	       const Vector<ValueType> &w); 
    
    protected:
    
    /**
     * Read only access operator to the underlying C array structure
     * associated with this vector.
     */
    inline
    const 
    ValueType* operator* () const
    {
      return (*this).data;
    }
    
    /**
     * Read-write access operator to the underlying C array structure
     * associated with this vector.
     */
    inline
    ValueType* operator* () 
    {
      return (*this).data;
    }
    
    private:
    
    /**
     * Internal reference to this vector size, ie. the number of
     * elements this vector has.
     */
    unsigned int n_el;
    
    /**
     * Internal object denoting this vector data.
     */
    ValueType *data;    
    
    
    }; /* Vector */

  /*-------------- Inline and Other Functions -----------------------*/

  template <typename ValueType>
    inline 
    const ValueType& 
    Vector<ValueType>::operator () (const unsigned int i) const
    {
      assert (i < n_el);
      return data[i];
    }
  
  template <typename ValueType>
    inline 
    ValueType& 
    Vector<ValueType>::operator () (const unsigned int i) 
    {
      assert (i < n_el);
      return data[i];
    }

  template <typename ValueType>
    inline 
    void
    Vector<ValueType>::operator += (const Vector<ValueType> &v) 
    {
      assert (v.n_el == this->n_el);
      for (unsigned int i=0; i<n_el; ++i)
	data[i] += v.data[i];
    }

  template <typename ValueType>
    inline 
    void
    Vector<ValueType>::operator = (const Vector<ValueType> &v) 
    {
      if (this->n_el != v.n_el)
	this->reinit (v.n_el);

      std::memcpy (this->data, v.data, sizeof (ValueType)*n_el);      
    }
  
  template <typename ValueType>
    inline 
    void
    Vector<ValueType>::operator -= (const Vector<ValueType> &v) 
    {
      assert (v.n_el == n_el);
      for (unsigned int i=0; i<n_el; ++i)
	data[i] -= v.data[i];
    }
  
  template <typename ValueType>
    inline 
    void
    Vector<ValueType>::operator *= (const ValueType &scalar) 
    {
      for (unsigned int i=0; i<n_el; ++i)
	data[i] *= scalar;
    }

  template <typename ValueType>
    inline 
    void
    Vector<ValueType>::operator /= (const ValueType &scalar) 
    {
      for (unsigned int i=0; i<n_el; ++i)
	data[i] /= scalar;
    }

  template <typename ValueType>
    inline 
    bool
    Vector<ValueType>::operator == (const Vector<ValueType> &v) const
    {
      assert (v.n_el == this->n_el);

      return static_cast<bool> (!std::memcmp (this->data, v.data, sizeof (ValueType)*n_el));
    }

  template <typename ValueType>
    inline
    unsigned int
    Vector<ValueType>::n_rows () const
    {
      return n_el;
    }

  template <typename ValueType>
    ValueType
    Vector<ValueType>::l1_norm () 
    {
      ValueType l1_norm = (ValueType) 0;

      for (unsigned int i=0; i<n_el; ++i)    
	l1_norm += std::fabs (data[i]);
      
      return l1_norm;
    }

  template <typename ValueType>
    ValueType
    Vector<ValueType>::l2_norm () 
    {
      ValueType l2_norm = (ValueType) 0;

      for (unsigned int i=0; i<n_el; ++i)    
	l2_norm += data[i] * data[i];

      return std::sqrt (l2_norm);
    }
  
  template <typename ValueType>
    ValueType
    Vector<ValueType>::lp_norm (const unsigned int p) 
    {
      assert (p>0);

      ValueType lp_norm = (ValueType) 0;

      for (unsigned int i=0; i<n_el; ++i)    
	lp_norm += std::pow (data[i], static_cast<ValueType> (p));
      
      return std::pow (lp_norm, (ValueType) 1./(ValueType) p); 
    }


  template <typename ValueType>
    inline
    void
    Vector<ValueType>::l2_normalize () 
    {
      ValueType l2_norm = this->l2_norm ();
      assert (l2_norm != (ValueType) 0);

      for (unsigned int i=0; i<n_el; ++i)    
	data[i] /= l2_norm;
    }

  template <typename ValueType>
    inline
    void
    Vector<ValueType>::lp_normalize (const unsigned int p) 
    {
      ValueType lp_norm = this->lp_norm (p);

      for (unsigned int i=0; i<n_el; ++i)    
	data[i] /= lp_norm;
    }

  template <typename ValueType>
    inline
    void
    Vector<ValueType>::diag (const Matrix<ValueType> &M) 
    {
      assert (M.n_rows () == M.n_cols ());
      assert (n_el    == M.n_rows ());

      if (n_el == 0) return;
      
      for (unsigned int i=0; i<n_el; ++i)
	data[i] = M(i, i);
    }

  template <typename ValueType>
    inline
    void
    Vector<ValueType>::sadd (const ValueType          a,
			     const Vector<ValueType> &v) 
    {
      assert (n_el   != 0);
      assert (v.n_el == n_el);

      for (unsigned int i=0; i<n_el; ++i)
	data[i] = a*v(i);
    }

  template <typename ValueType>
    inline
    void
    Vector<ValueType>::sadd (const ValueType          a,
			     const Vector<ValueType> &v,
			     const ValueType          b,
			     const Vector<ValueType> &w) 
    {
      assert (n_el   != 0);
      assert (v.n_el == n_el);

      for (unsigned int i=0; i<n_el; ++i)
	data[i] = a*v(i) + b*w(i);
    }

} /* namespace ewalena */
  
#endif /* __ewalena_vector_h */
  
