/**
 * The MIT License (MIT)
 *
 * Copyright (c) <2015> <Romain LEGUAY romain.leguay@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
**/
/*
 * ResultPolicy.hxx
 *
 *  Created on: 24 févr. 2015
 *      Author: rleguay
 */

#ifndef RESULTPOLICY_HXX_
#define RESULTPOLICY_HXX_

#include "Policy.hxx"

namespace policy
{
  /**
   * The class do nothing with the result passed to it's arguments
   */
  typedef NoPolicy NoResultPolicy;

  class AddNumberResultPolicy
  {
  public:
    AddNumberResultPolicy()
  {
  }

    virtual ~AddNumberResultPolicy()
    {
    }

    template<typename OutputResult>
    void applyResult(OutputResult * out, OutputResult * otherValue)
    {
      *out += *otherValue;
    }
  };
} // namespace policy

#endif /* RESULTPOLICY_HXX_ */
