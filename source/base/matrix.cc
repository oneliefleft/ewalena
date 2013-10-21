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

#include <ewalena/base/matrix.h>
#include <ewalena/base/tensor.h>

namespace ewalena
{
 
  template <typename ValueType>
  Matrix<ValueType>::Matrix ()
    :
    __n_rows (0),
    __n_cols (0),
    data (new ValueType[0])
  {}
  
  template <typename ValueType>
  Matrix<ValueType>::Matrix (const unsigned int m, 
			     const unsigned int n,
			     const bool         zero)
    :
    __n_rows (m),
    __n_cols (n),
    data (new ValueType[m*n])
  {
    if (zero)
      this->reinit ();
  }
  
  template <typename ValueType>
  Matrix<ValueType>::Matrix (std::pair<const unsigned int, const unsigned int> mn_pair,
			     const bool                                        zero)
    :
    __n_rows (mn_pair.first),
    __n_cols (mn_pair.second),
    data (new ValueType[__n_rows*__n_cols])
  {
    if (zero)
      this->reinit ();
  }

  template <typename ValueType>
  Matrix<ValueType>::Matrix (const Matrix<ValueType> &M)
    :
    __n_rows (M.n_rows ()),
    __n_cols (M.n_cols ()),
    data (new ValueType[__n_rows*__n_cols])
  {
    if (this->data)
      std::memcpy (this->data, M.data, sizeof (ValueType) * this->__n_rows*this->__n_cols);
  }

  
  template <typename ValueType>
  Matrix<ValueType>::~Matrix ()
  {
    // Contents don't matter - just blowm away whatever is there.
    delete[] this->data;
  }

  template <typename ValueType>
  void
  Matrix<ValueType>::reinit (const unsigned int m,
			     const unsigned int n,
			     const bool         zero) 
  {
    if (data)
      delete[] this->data;

    this->__n_rows = m;
    this->__n_cols = n;
    this->data     = new ValueType [this->__n_rows*this->__n_cols];

                                 // Zero out the memory pertaining to
                                 // this new vector.
    if (zero)
      this->reinit ();
  }
    
  template <typename ValueType>
  void
  Matrix<ValueType>::reinit () 
  {
    // Zero out matrix memory.
    std::memset (data, 0, sizeof (ValueType) * this->__n_rows*this->__n_cols);
  }

} // namepsace ewalena


// -------------- Explicit Instantiations -------------------------------


template class ewalena::Matrix<double>;
template class ewalena::Matrix<std::complex<double>>;




