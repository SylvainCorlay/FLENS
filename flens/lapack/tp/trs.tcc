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

/* Based on
 *
       SUBROUTINE DTPTRS( UPLO, TRANS, DIAG, N, NRHS, AP, B, LDB, INFO )
       SUBROUTINE ZTPTRS( UPLO, TRANS, DIAG, N, NRHS, AP, B, LDB, INFO )
 *
 *  -- LAPACK routine (version 3.3.1) --
 *  -- LAPACK is a software package provided by Univ. of Tennessee,    --
 *  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
 *  -- April 2011                                                      --
 *
 */

#ifndef FLENS_LAPACK_TP_TRS_TCC
#define FLENS_LAPACK_TP_TRS_TCC 1

#include <flens/blas/blas.h>
#include <flens/lapack/lapack.h>

namespace flens { namespace lapack {

//== interface for external lapack =============================================

#ifdef USE_CXXLAPACK

namespace external {

//-- (tp)trs [real and complex variant] ----------------------------------------

template <typename MA, typename MB>
typename TpMatrix<MA>::IndexType
trs_impl(Transpose trans, const TpMatrix<MA> &A, GeMatrix<MB> &B)
{
    typedef typename TpMatrix<MA>::IndexType  IndexType;

    IndexType info;
    info = cxxlapack::tbtrs<IndexType>(getF77Char(A.upLo()),
                                       getF77Char(trans),
                                       getF77Char(A.diag()),
                                       A.dim(),
                                       B.numCols(),
                                       A.data(),
                                       A.leadingDimension(),
                                       B.data(),
                                       B.leadingDimension());
    ASSERT(info>=0);
    return info;
}

} // namespace external

#endif // USE_CXXLAPACK


//== public interface ==========================================================

#ifdef USE_CXXLAPACK

//-- (tp)trs [real and complex variant] ----------------------------------------

template <typename MA, typename MB>
typename RestrictTo<IsTpMatrix<MA>::value
                 && IsGeMatrix<MB>::value,
         typename RemoveRef<MA>::Type::IndexType>::Type
trs(Transpose trans, const MA &A, MB &&B)
{
    LAPACK_DEBUG_OUT("(tp)trs [real/complex]");
//
//  Remove references from rvalue types
//
    typedef typename RemoveRef<MA>::Type    MatrixA;
    typedef typename MatrixA::IndexType     IndexType;

//
//  Test the input parameters
//
#   ifndef NDEBUG
    ASSERT(A.firstRow()==1);
    ASSERT(A.firstCol()==1);

    const IndexType n = A.dim();

    ASSERT(B.firstRow()==1);
    ASSERT(B.firstCol()==1);
    ASSERT(B.numRows()==n);
#   endif

//
//  Call implementation
//
    IndexType info = external::trs_impl(trans, A, B);

    return info;
}

//-- (tp)trs [variant if rhs is vector] ----------------------------------------

template <typename MA, typename VB>
typename RestrictTo<IsTpMatrix<MA>::value
                 && IsDenseVector<VB>::value,
         typename RemoveRef<MA>::Type::IndexType>::Type
trs(Transpose trans, const MA &A, VB &&b)
{
//
//  Remove references from rvalue types
//
    typedef typename RemoveRef<MA>::Type    MatrixA;
    typedef typename RemoveRef<VB>::Type    VectorB;

//
//  Create matrix view from vector b and call above variant
//
    typedef typename VectorB::ElementType  ElementType;
    typedef typename VectorB::IndexType    IndexType;

    const IndexType    n     = b.length();
    const StorageOrder order = MatrixA::Engine::order;

    GeMatrix<FullStorageView<ElementType, order> >  B(n, 1, b, n);

    return trs(trans, A, B);
}

#endif // USE_CXXLAPACK


} } // namespace lapack, flens

#endif // FLENS_LAPACK_TP_TRS_TCC
