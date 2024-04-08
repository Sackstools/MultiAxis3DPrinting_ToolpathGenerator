// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2012 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_REF_H
#define EIGEN_REF_H

namespace Eigen { 

// traits class for Ref class template
namespace internal {

template<typename _PlainObjectType, int _Options, typename _StrideType>
struct traits<Ref<_PlainObjectType, _Options, _StrideType> >
  : public traits<Map<_PlainObjectType, _Options, _StrideType> >
{
  //... (code elided for brevity)

  // struct match to check if the given Derived type matches the Ref type
  template<typename Derived> struct match {
    //... (code elided for brevity)

    // type is true_type if all the conditions are satisfied, false_type otherwise
    typedef typename internal::conditional<MatchAtCompileTime,internal::true_type,internal::false_type>::type type;
  };
};

// traits class for RefBase class template
template<typename Derived>
struct traits<RefBase<Derived> > : public traits<Derived> {};

} // end namespace internal

// RefBase class template
template<typename Derived> class RefBase
 : public MapBase<Derived>
{
  //... (code elided for brevity)

protected:

  // Stride type for the RefBase class
  typedef Stride<StrideType::OuterStrideAtCompileTime,StrideType::InnerStrideAtCompileTime> StrideBase;

  // construct method to construct the RefBase object from an Expression object
  template<typename Expression>
  EIGEN_DEVICE_FUNC void construct(Expression& expr)
  {
    //... (code elided for brevity)
  }

  // StrideBase member variable
  StrideBase m_stride;
};

// Ref class template
/** \class Ref
  * \ingroup Core_Module
  *
  * \brief A matrix or vector expression mapping an existing expression
  *
  * \tparam PlainObjectType the equivalent matrix type of the mapped data
  * \tparam Options specifies the pointer alignment in bytes. It can be: \c #Aligned128, , \c #Aligned64, \c #Aligned32, \c #Aligned16, \c #Aligned8 or \c #Unaligned.
  *                 The default is \c #Unaligned.
  * \tparam StrideType optionally specifies strides. By default, Ref implies a contiguous storage along the inner dimension (inner stride==1),
  *                   but accepts a variable outer stride (leading dimension).
  *                   This can be overridden by specifying strides.
  *                   The type passed here must be a specialization of the Stride template, see examples below.
  *
  * This class provides a way to write non-template functions taking Eigen objects as parameters while limiting the number of copies.
  * A Ref<> object can represent either a const expression or a l-value:
  * \code
  * // in-out argument:
  * void foo1(Ref<VectorXf> x);
  *
  * // read-only const argument:
  * void foo2(const Ref<const VectorXf>& x);
  * \endcode
  *
  * In the in-out case, the input argument must satisfy the constraints of the actual Ref<> type, otherwise a compilation issue will be triggered.
  * By default, a Ref<VectorXf> can reference any dense vector expression of float having a contiguous memory layout.
  * Likewise, a Ref<MatrixXf> can reference any column-major dense matrix expression of float whose column's elements are contiguously stored with
  * the possibility to have a constant space in-between each column, i.e. the inner stride must be equal to 1, but the outer stride (or leading dimension)
  * can be greater than the number of rows.
  *
  * In the const case, if the input expression does not match the above requirement, then it is evaluated into a temporary before being passed to the function.
  * Here are some examples:
  * \code
  * MatrixXf A;
  * VectorXf a;
  * foo1(a.head());             // OK
  * foo1(A.col());              // OK
  * foo1(A.row());              // Compilation error because here innerstride!=1
  * foo2(A.row());              // Compilation error because A.row() is a 1xN object while foo2 is expecting a Nx1 object
  * foo2(A.row().transpose());  // The row is copied into a contiguous temporary
  * foo2(2*a);                  // The expression is evaluated into a temporary
  * foo2(A.col().segment(2,4)); // No temporary
  * \endcode
  *
  * The range of inputs that can be referenced without temporary can be enlarged using the last two template parameters.
  * Here is an example accepting an innerstride!=1:
  * \code
  * // in-out argument:
  * void foo3(Ref<VectorXf,0,InnerStride<> > x);
  * foo3(A.row());              // OK
  * \endcode
  * The downside here is that the function foo3 might be significantly slower than foo1 because it won't be able to exploit vectorization, and will involve more
  * expensive address computations even if the input is contiguously stored in memory. To overcome this issue, one might propose to overload internally calling a
  * template function, e.g.:
  * \code
  * // in the .h:
  * void foo(const Ref<MatrixXf>& A);
  * void foo(const Ref<MatrixXf,0
