// Copyright notice and licensing information.

#ifndef EIGEN_SELFADJOINT_MATRIX_MATRIX_BLAS_H
#define EIGEN_SELFADJOINT_MATRIX_MATRIX_BLAS_H

// Eigen namespace declaration.
namespace Eigen {

// Internal namespace declaration.
namespace internal {

// Macro definitions for optimized self-adjoint matrix-matrix products using
// BLAS functions. The macros define the product_selfadjoint_matrix struct
// template with a run() function that performs the matrix product using
// BLAS functions.

// EIGEN_BLAS_SYMM_L: Defines a macro for self-adjoint matrix-matrix product
//   with left-side multiplication using the ?SYMM BLAS function.
// EIGEN_BLAS_HEMM_L: Defines a macro for self-adjoint matrix-matrix product
//   with left-side multiplication using the ?HEMM BLAS function.
// EIGEN_BLAS_SYMM_R: Defines a macro for self-adjoint matrix-matrix product
//   with right-side multiplication using the ?SYMM BLAS function.
// EIGEN_BLAS_HEMM_R: Defines a macro for self-adjoint matrix-matrix product
//   with right-side multiplication using the ?HEMM BLAS function.

// The macros use the following predefined parameters:
// EIGTYPE: The Eigen type of the matrices (float, double, std::complex<float>,
//          or std::complex<double>).
// BLASTYPE: The BLAS type of the matrices (float, double, MKL_Complex8, or
//           MKL_Complex16).
// EIGPREFIX: The Eigen prefix for the matrix type (f, d, cf, or cd).
// BLASFUNC: The BLAS function name (ssymm, dsymm, chemm, or zhemm).

// The macros use the following template parameters:
// Index: The index type (int or long).
// LhsStorageOrder: The storage order of the left-hand side matrix (RowMajor
//                  or ColMajor).
// ConjugateLhs: A boolean flag indicating whether to conjugate the left-hand
//               side matrix.
// RhsStorageOrder: The storage order of the right-hand side matrix (RowMajor
//                  or ColMajor).
// ConjugateRhs: A boolean flag indicating whether to conjugate the right-hand
//               side matrix.

// The macros use the following function parameters:
// rows: The number of rows of the result matrix.
// cols: The number of columns of the result matrix.
// _lhs: A pointer to the first element of the left-hand side matrix.
// lhsStride: The number of elements between two consecutive rows of the
//             left-hand side matrix.
// _rhs: A pointer to the first element of the right-hand side matrix.
// rhsStride: The number of elements between two consecutive rows of the
//             right-hand side matrix.
// res: A pointer to the first element of the result matrix.
// resStride: The number of elements between two consecutive rows of the
//             result matrix.
// alpha: A scalar value that multiplies the left-hand side matrix.
// blocking: A level3_blocking object used for blocking the computation.

// The macros define the product_selfadjoint_matrix struct template with a
// run() function that performs the matrix product using BLAS functions.
// The run() function sets the side, uplo, m, n, lda, ldb, ldc, a, b, and beta
// parameters for the BLAS function and calls the BLAS function using the
// provided parameters.

// Conditional compilation directives for using either the Intel MKL BLAS
// library or the reference BLAS implementation.

#ifdef EIGEN_USE_MKL
EIGEN_BLAS_SYMM_L(double, double, d, dsymm)
EIGEN_BLAS_SYMM_L(float, float, f, ssymm)
EIGEN_BLAS_HEMM_L(dcomplex, MKL_Complex16, cd, zhemm)
EIGEN_BLAS_HEMM_L(scomplex, MKL_Complex8, cf, chemm)

EIGEN_BLAS_SYMM_R(double, double, d, dsymm)
EIGEN_BLAS_SYMM_R(float, float, f, ssymm)
EIGEN_BLAS_HEMM_R(dcomplex, MKL_Complex16, cd, zhemm)
EIGEN_BLAS_HEMM_R(scomplex, MKL_Complex8, cf, chemm)
#else
EIGEN_BLAS_SYMM_L(double, double, d, dsymm_)
EIGEN_BLAS_SYMM_L(float, float, f, ssymm_)
EIGEN_BLAS_HEMM_L(dcomplex, double, cd, zhemm_)
EIGEN_BLAS_HEMM_L(scomplex, float, cf, chemm_)

EIGEN_BLAS_SYMM_R(double, double, d, dsymm_)
EIGEN_BLAS_SYMM_R(float, float, f, ssymm_)
EIGEN_BLAS_HEMM_R(dcomplex, double, cd, zhemm_)
EIGEN_BLAS_HEMM_R(scomplex, float, cf, chemm_)
#endif

} // end namespace internal

} // end namespace Eigen

#endif // EIGEN_SELFADJOINT_MATRIX_MATRIX_BLAS_H
