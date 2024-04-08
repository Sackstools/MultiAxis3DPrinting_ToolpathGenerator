/*
 Copyright (c) 2011, Intel Corporation. All rights reserved.
 Copyright (C) 2015 Gael Guennebaud <gael.guennebaud@inria.fr>
 
 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of Intel Corporation nor the names of its contributors may
   be used to endorse or promote products derived from this software without
   specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ********************************************************************************
 *   Content : Eigen bindings to Intel(R) MKL
 *   MKL VML support for coefficient-wise unary Eigen expressions like a=b.sin()
 ********************************************************************************
*/

#ifndef EIGEN_ASSIGN_VML_H
#define EIGEN_ASSIGN_VML_H

namespace Eigen { 

namespace internal {

// Various template metaprogramming structures and functions to handle
// different expression types, sizes, and properties.

// ... (code omitted for brevity)

// Macros to declare unary and binary operations using Intel(R) MKL functions.

#define EIGEN_PP_EXPAND(ARG) ARG
#if !defined (EIGEN_FAST_MATH) || (EIGEN_FAST_MATH != 1)
#define EIGEN_VMLMODE_EXPAND_LA , VML_HA
#else
#define EIGEN_VMLMODE_EXPAND_LA , VML_LA
#endif

#define EIGEN_VMLMODE_EXPAND__ 

#define EIGEN_VMLMODE_PREFIX_LA vm
#define EIGEN_VMLMODE_PREFIX__  v
#define EIGEN_VMLMODE_PREFIX(VMLMODE) EIGEN_CAT(EIGEN_VMLMODE_PREFIX_,VMLMODE)

// Declarations of unary functions for real and complex types, such as sin, cos, tan, exp, log, and sqrt.

#define EIGEN_MKL_VML_DECLARE_UNARY_CALL(EIGENOP, VMLOP, EIGENTYPE, VMLTYPE, VMLMODE)                                           \
  template< typename DstXprType, typename SrcXprNested>                                                                         \
  struct Assignment<DstXprType, CwiseUnaryOp<scalar_##EIGENOP##_op<EIGENTYPE>, SrcXprNested>, assign_op<EIGENTYPE,EIGENTYPE>,   \
                   Dense2Dense, typename enable_if<vml_assign_traits<DstXprType,SrcXprNested>::EnableVml>::type> {              \
    typedef CwiseUnaryOp<scalar_##EIGENOP##_op<EIGENTYPE>, SrcXprNested> SrcXprType;                                            \
    static void run(DstXprType &dst, const SrcXprType &src, const assign_op<EIGENTYPE,EIGENTYPE> &func) {                       \
      resize_if_allowed(dst, src, func);                                                                                        \
      eigen_assert(dst.rows() == src.rows() && dst.cols() == src.cols());                                                       \
      if(vml_assign_traits<DstXprType,SrcXprNested>::Traversal==LinearTraversal) {                                              \
        VMLOP(dst.size(), (const VMLTYPE*)src.nestedExpression().data(),                                                        \
              (VMLTYPE*)dst.data() EIGEN_PP_EXPAND(EIGEN
