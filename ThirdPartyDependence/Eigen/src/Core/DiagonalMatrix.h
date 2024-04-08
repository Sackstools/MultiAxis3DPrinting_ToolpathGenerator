// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2009 Gael Guennebaud <gael.guennebaud@inria.fr>
// Copyright (C) 2007-2009 Benoit Jacob <jacob.benoit.1@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_DIAGONALMATRIX_H
#define EIGEN_DIAGONALMATRIX_H

namespace Eigen { 

// DiagonalBase is the base class for DiagonalMatrix and DiagonalWrapper.
// It provides common functionality for diagonal matrices.

// DiagonalVectorType is the type of the vector of diagonal coefficients.
// Scalar is the type of coefficients.
// StorageKind is the storage kind of the diagonal matrix.
// StorageIndex is the index type.

// The following enum defines the number of rows and columns at compile time,
// the maximum number of rows and columns at compile time, and flags.

// DenseMatrixType is the type of the dense matrix.
// DenseType is an alias for DenseMatrixType.
// PlainObject is the type of the diagonal matrix.

// The following functions return the derived class, the number of rows and columns,
// and the diagonal vector.

// The following template function defines the product of a diagonal matrix and another matrix.

// The following function returns the inverse of the diagonal matrix.

// The following function multiplies the diagonal matrix by a scalar.

// The following friend function multiplies a scalar by a diagonal matrix.

// The following template class represents a diagonal matrix with its storage.

// The following struct defines the traits of the DiagonalMatrix class.

// The following constructor initializes the diagonal matrix with a given size.

// The following constructor initializes the diagonal matrix with given diagonal coefficients.

// The following copy constructor initializes the diagonal matrix with another diagonal matrix.

// The following constructor initializes the diagonal matrix with an expression of the diagonal coefficients.

// The following copy operator assigns another diagonal matrix to the current diagonal matrix.

// The following function resizes the diagonal matrix.

// The following function sets all coefficients to zero.

// The following function resizes and sets all coefficients to zero.

// The following function sets the diagonal matrix to be the identity matrix.

// The following class represents an expression of a diagonal matrix.

// The following struct defines the traits of the DiagonalWrapper class.

// The following constructor initializes the diagonal wrapper with an expression of diagonal coefficients.

// The following function returns a const reference to the wrapped expression of diagonal coefficients.

// The following function converts a matrix to a diagonal matrix.

// The following function checks if a matrix is approximately diagonal.

} // end namespace Eigen

#endif // EIGEN_DIAGONALMATRIX_H
