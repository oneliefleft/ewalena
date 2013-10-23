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

#include <ewalena/base/tensor.h>

#include <cmath>

namespace ewalena
{
 
  template <int dim, int rank, typename ValueType>
  Tensor<dim, rank, ValueType>::Tensor (const bool zero)
    :
    __n_components (static_cast<unsigned int> (math::pow (dim, rank))),
    data (new ValueType[__n_components])
  {
    if (zero)
      reinit ();
  }
 
  template <int dim, int rank, typename ValueType>
  Tensor<dim, rank, ValueType>::Tensor (const Tensor<dim, rank, ValueType> &T)
    :
    __n_components (T.__n_components),
    data (new ValueType[__n_components])
  {
    if (__n_components != 0)
      std::memcpy (this->data, T.data, sizeof (ValueType)*__n_components);
  }

  template <int dim, int rank, typename ValueType>
  Tensor<dim, rank, ValueType>::~Tensor ()
  {
    // Contents don't matter - set the pointer to NULL.
    delete[] this->data;
  }
  
  template <int dim, int rank, typename ValueType>
  void
  Tensor<dim, rank, ValueType>::clone (const Tensor<dim, rank, ValueType> &T)
  {
    std::memcpy (this->data, T.data, sizeof (ValueType)*__n_components);
  }
  
  template <int dim, int rank, typename ValueType>
  std::pair<unsigned int, unsigned int>
  Tensor<dim, rank, ValueType>::voight_components () const
  {
    
    // This operation is undefined for rank 0 tensors.
    assert (rank > 0);
    assert (data);
    
    switch (rank)
      {
      case 1:
	// row, col
	return { 1, dim }; 
	
      case 2:
	// row, col
	return { 1, (unsigned int) (dim*(dim-1)/2)+dim };
	
      default:
	
	// The size (m,n) of a Voight matrix with respect to the
	// original tensor is \f$(d*m, d*n)\f$ where \f$m\f$ is the
	// tensor rank over two and \f$n\f$ is \f$m\f$ plus the
	// remainder. Note: \f$m$ and \f$n\f are meaningfully
	// interchangable.
	div_t size;
	size = div (rank, 2);
	
	const unsigned int n_rows = dim*size.quot;
	const unsigned int n_cols = dim*(size.quot+size.rem);
	
	// row, col
	return { n_rows, n_cols };
      }
  }
  
  
  template <int dim, int rank, typename ValueType>
  void
  Tensor<dim, rank, ValueType>::reinit () 
  {
    // Zero out tensor memory.
    std::memset (data, ValueType(0), sizeof (ValueType)*__n_components);
  }
  
} // namepsace ewalena

// -------------- Explicit Instantiations -------------------------------

template class ewalena::Tensor<1, 1, double>;
template class ewalena::Tensor<2, 1, double>;
template class ewalena::Tensor<3, 1, double>;

template class ewalena::Tensor<1, 2, double>;
template class ewalena::Tensor<2, 2, double>;
template class ewalena::Tensor<3, 2, double>;

template class ewalena::Tensor<1, 3, double>;
template class ewalena::Tensor<2, 3, double>;
template class ewalena::Tensor<3, 3, double>;

template class ewalena::Tensor<1, 4, double>;
template class ewalena::Tensor<2, 4, double>;
template class ewalena::Tensor<3, 4, double>;

template class ewalena::Tensor<1, 6, double>;
template class ewalena::Tensor<2, 6, double>;
template class ewalena::Tensor<3, 6, double>;

