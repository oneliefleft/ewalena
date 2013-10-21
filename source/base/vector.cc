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

#include <ewalena/base/vector.h>

namespace ewalena 
{
  
  template <typename ValueType>
  Vector<ValueType>::Vector ()
    :
    n_el (0),
    data (new ValueType[0])
  {}
  
  template <typename ValueType>
  Vector<ValueType>::Vector (const unsigned int m,
			     const bool         zero)
    :
    n_el (m),
    data (new ValueType[n_el])
  {
    if (zero)
      reinit ();
  }

  template <typename ValueType>
  Vector<ValueType>::Vector (const Vector<ValueType> &v)
    :
    n_el (v.n_rows ()),
    data (new ValueType[n_el])
  {
    if (n_el != 0)
      std::memcpy (this->data, v.data, sizeof (ValueType)*n_el);
  }

  template <typename ValueType>
  Vector<ValueType>::Vector (std::initializer_list<ValueType> list) 
    :
    n_el (list.size ()),
    data (new ValueType[n_el])
  {
    if (n_el != 0)
      std::copy (list.begin(), list.end(), this->data);
  }

  template <typename ValueType>
  Vector<ValueType>::~Vector ()
  {
    // Blow away whatever is there if something is there.
    delete[] this->data;
  }

  
  template <typename ValueType>
  void
  Vector<ValueType>::reinit () 
  {
    // Zero out the memory pertaining to this vector by brute force.
    std::memset (data, 0, sizeof (ValueType)*n_el);
  }
  
  template <typename ValueType>
  unsigned int
  Vector<ValueType>::size () const 
  {
    return this->n_el;
  }

  template <typename ValueType>
  void
  Vector<ValueType>::reinit (const unsigned int m,
			     const bool         zero) 
  {
    if (data)
      delete[] this->data;
    
    n_el = m;
    data     = new ValueType [n_el];
    
    // Zero out the memory pertaining to this new vector.
    if (zero)
      std::memset (data, 0, sizeof (ValueType)*n_el);
  }
  
} // namespace ewalena


// -------------- Explicit Instantiations -------------------------------


template class ewalena::Vector<double>;
template class ewalena::Vector<std::complex<double>>;

