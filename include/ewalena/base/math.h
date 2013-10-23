// -------------------------------------------------------------------
// @author Toby D. Young
// @version $Id: utilities.h 1015 2013-08-06 12:20:12Z oneliefleft $
//
// Copyright 2012 namespace ewalena authors. All rights reserved.
//
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

#ifndef __ewalena_math_h
#define __ewalena_math_h

#include <cassert>

namespace ewalena 
{
  
  /**
   * Some math utilities and functions.
   */
  namespace math
  {

    /**
     * Return the sign of this scalar number as an integer \f$\pm1\f$.
     *
     * @note \f$\text{sgn}[0]\f$ is not defined and in that case an
     * exception is triggered. To avoid that, an assertion should
     * always be put in an application code.
     */
    template <typename ValueType>
      int sgn (const ValueType scalar);
    
    /**
     * Return the incomplete gamma function of this scalar number.
     */
    template <typename ValueType>
      ValueType incomplete_gamma (const ValueType scalar);
    
    /**
     * Return \f$p=x^y\f$ where \f$p,x,y\in\{0,{\mathbb I}^+\}\f$.
     */
    unsigned int pow (const unsigned int x, 
		      const unsigned int y);

    /**
     * Return the factorial of \f$x\f$: \f$x!\f$.
     */
    unsigned int factorial (const unsigned int x);

    /**
     * Return the true (false) if this integer value is odd (even).
     */
    bool is_odd (const int scalar);    
    
    /**
     * Return the true (false) if this integer value is even (odd).
     */
    bool is_even (const int scalar);    
    
    /**
     * \f$pi\f$
     */
    static const double  PI      = 3.14159265358979323846;
    
    /**
     * \f$\frac{pi}{2}\f$
     */
    static const double  PI_2    = 1.57079632679489661923;
    
    /**
     * \f$\frac{pi}{4}\f$
     */
    static const double  PI_4    = 0.78539816339744830962;
    
    /**
     * \f$sqrt(2)\f$
     */
    static const double  SQRTo2  = 1.41421356237309504880;
    
  }


  /*-------------- Inline and Other Functions -----------------------*/

  inline 
    unsigned int math::pow (const unsigned int x, 
			    const unsigned int y)
  {
    return (y == 0) 
      ? 1 
      : x * (pow (x, y-1));
  }
  
  inline
    unsigned int math::factorial (const unsigned int x)
  {
    return (x == 1 || x == 0) 
      ? 1 
      : factorial (x-1)*x;
  }
  
} /* namespace ewalena */

#endif /* __ewalena_math_h */
