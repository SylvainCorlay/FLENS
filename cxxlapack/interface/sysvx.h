/*
 *   Copyright (c) 2012, Michael Lehn, Klaus Pototzky
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3) Neither the name of the FLENS development group nor the names of
 *      its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CXXLAPACK_INTERFACE_SYSVX_H
#define CXXLAPACK_INTERFACE_SYSVX_H 1

#include <cxxstd/complex.h>

namespace cxxlapack {

template <typename IndexType>
    IndexType
    sysvx(char                  fact,
          char                  uplo,
          IndexType             n,
          IndexType             nRhs,
          const float           *A,
          IndexType             ldA,
          float                 *Af,
          IndexType             ldAf,
          IndexType             *iPiv,
          const float           *B,
          IndexType             ldB,
          float                 *X,
          IndexType             ldX,
          float                 &rCond,
          float                 *ferr,
          float                 *berr,
          float                 *work,
          IndexType             lWork,
          IndexType             *iWork);


template <typename IndexType>
    IndexType
    sysvx(char                  fact,
          char                  uplo,
          IndexType             n,
          IndexType             nRhs,
          const double          *A,
          IndexType             ldA,
          double                *Af,
          IndexType             ldAf,
          IndexType             *iPiv,
          const double          *B,
          IndexType             ldB,
          double                *X,
          IndexType             ldX,
          double                &rCond,
          double                *ferr,
          double                *berr,
          double                *work,
          IndexType             lWork,
          IndexType             *iWork);

template <typename IndexType>
    IndexType
    sysvx(char                        fact,
          char                        uplo,
          IndexType                   n,
          IndexType                   nRhs,
          const std::complex<float >  *A,
          IndexType                   ldA,
          std::complex<float >        *Af,
          IndexType                   ldAf,
          IndexType                   *iPiv,
          const std::complex<float >  *B,
          IndexType                   ldB,
          std::complex<float >        *X,
          IndexType                   ldX,
          float                       &rCond,
          float                       *ferr,
          float                       *berr,
          std::complex<float >        *work,
          IndexType                   lWork,
          float                       *rWork);

template <typename IndexType>
    IndexType
    sysvx(char                        fact,
          char                        uplo,
          IndexType                   n,
          IndexType                   nRhs,
          const std::complex<double>  *A,
          IndexType                   ldA,
          std::complex<double>        *Af,
          IndexType                   ldAf,
          IndexType                   *iPiv,
          const std::complex<double>  *B,
          IndexType                   ldB,
          std::complex<double>        *X,
          IndexType                   ldX,
          double                      &rCond,
          double                      *ferr,
          double                      *berr,
          std::complex<double>        *work,
          IndexType                   lWork,
          double                      *rWork);

} // namespace cxxlapack

#endif // CXXLAPACK_INTERFACE_SYSVX_H
