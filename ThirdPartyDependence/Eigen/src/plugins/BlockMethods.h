/**
 * This file is part of Eigen, a lightweight C++ template library
 * for linear algebra.
 *
 * Copyright (C) 2008-2010 Gael Guennebaud <gael.guennebaud@inria.fr>
 * Copyright (C) 2006-2010 Benoit Jacob <jacob.benoit.1@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla
 * Public License v. 2.0. If a copy of the MPL was not distributed
 * with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


/**
 * \returns an expression of a block in \c *this with either dynamic or fixed sizes.
 *
 * \param  startRow  the first row in the block
 * \param  startCol  the first column in the block
 * \param  blockRows number of rows in the block, specified at either run-time or compile-time
 * \param  blockCols number of columns in the block, specified at either run-time or compile-time
 * \tparam NRowsType the type of the value handling the number of rows in the block, typically Index.
 * \tparam NColsType the type of the value handling the number of columns in the block, typically Index.
 *
 * Example using runtime (aka dynamic) sizes: \include MatrixBase_block_int_int_int_int.cpp
 * Output: \verbinclude MatrixBase_block_int_int_int_int.out
 *
 * \newin{3.4}:
 *
 * The number of rows \a blockRows and columns \a blockCols can also be specified at compile-time by passing Eigen::fix<N>,
 * or Eigen::fix<N>(n) as arguments. In the later case, \c n plays the role of a runtime fallback value in case \c N equals Eigen::Dynamic.
 * Here is an example with a fixed number of rows \c NRows and dynamic number of columns \c cols:
 * \code
 * mat.block(i,j,fix<NRows>,cols)
 * \endcode
 *
 * This function thus fully covers the features offered by the following overloads block<NRows,NCols>(Index, Index),
 * and block<NRows,NCols>(Index, Index, Index, Index) that are thus obsolete. Indeed, this generic version avoids
 * redundancy, it preserves the argument order, and prevents the need to rely on the template keyword in templated code.
 *
 * \note Even in the case that the returned expression has dynamic size, in the case
 * when it is applied to a fixed-size matrix, it inherits a fixed maximal size,
 * which means that evaluating it does not cause a dynamic memory allocation.
 *
 * EIGEN_DOC_BLOCK_ADDONS_NOT_INNER_PANEL
 *
 * \sa class Block, fix, fix<N>(int)
 *
 */
template<typename NRowsType, typename NColsType>
EIGEN_DEVICE_FUNC
#ifndef EIGEN_PARSED_BY_DOXYGEN
inline typename FixedBlockXpr<internal::get_fixed_value<NRowsType>::value,internal::get_fixed_value<NColsType>::value>::Type
#else
inline typename FixedBlockXpr<...,...>::Type
#endif
block(Index startRow, Index startCol, NRowsType blockRows, NColsType blockCols)
{
  return typename FixedBlockXpr<internal::get_fixed_value<NRowsType>::value,internal::get_fixed_value<NColsType>::value>::Type(
            derived(), startRow, startCol, internal::get_runtime_value(blockRows), internal::get_runtime_value(blockCols));
}


/// \internal expression type of a column */
typedef Block<Derived, internal::traits<Derived>::RowsAtCompileTime, 1, !IsRowMajor> ColXpr;
typedef const Block<const Derived, internal::traits<Derived>::RowsAtCompileTime, 1, !IsRowMajor> ConstColXpr;
/// \internal expression type of a row */
typedef Block<Derived, 1, internal::traits<Derived>::ColsAtCompileTime, IsRowMajor> RowXpr;
typedef const Block<const Derived, 1, internal::traits<Derived>::ColsAtCompileTime, IsRowMajor> ConstRowXpr;
