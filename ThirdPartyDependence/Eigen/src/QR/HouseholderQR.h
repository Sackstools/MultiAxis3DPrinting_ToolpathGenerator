// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.


namespace Eigen { 

template<typename _MatrixType> class HouseholderQR
{
  public:
    // ...
};

} // end namespace Eigen

#endif // EIGEN_QR_H


/** Default Constructor.
  *
  * The default constructor is useful in cases in which the user intends to
  * perform decompositions via HouseholderQR::compute(const MatrixType&).
  */
HouseholderQR() : m_qr(), m_hCoeffs(), m_temp(), m_isInitialized(false) {}

/** \brief Default Constructor with memory preallocation
  *
  * Like the default constructor but with preallocation of the internal data
  * according to the specified problem \a size.
  * \sa HouseholderQR()
  */
HouseholderQR(Index rows, Index cols)
  : m_qr(rows, cols),
    m_hCoeffs((std::min)(rows,cols)),
    m_temp(cols),
    m_isInitialized(false) {}

/** \brief Constructs a QR factorization from a given matrix
  *
  * This constructor computes the QR factorization of the matrix \a matrix by calling
  * the method compute(). It is a short cut for:
  *
  * \code
  * HouseholderQR<MatrixType> qr(matrix.rows(), matrix.cols());
  * qr.compute(matrix);
  * \endcode
  *
  * \sa compute()
  */
template<typename InputType>
explicit HouseholderQR(const EigenBase<InputType>& matrix)
  : m_qr(matrix.rows(), matrix.cols()),
    m_hCoeffs((std::min)(matrix.rows(),matrix.cols())),
    m_temp(matrix.cols()),
    m_isInitialized(false)
{
  compute(matrix.derived());
}

/** \brief Constructs a QR factorization from a given matrix
  *
  * This overloaded constructor is provided for \link InplaceDecomposition inplace decomposition \endlink when
  * \c MatrixType is a Eigen::Ref.
  *
  * \sa HouseholderQR(const EigenBase&)
  */
template<typename InputType>
explicit HouseholderQR(EigenBase<InputType>& matrix)
  : m_qr(matrix.derived()),
    m_hCoeffs((std::min)(matrix.rows(),matrix.cols())),
    m_temp(matrix.cols()),
    m_isInitialized(false)
{
  computeInPlace();
}

/** This method finds a solution x to the equation Ax=b, where A is the matrix of which
  * *this is the QR decomposition, if any exists.
  *
  * \param b the right-hand-side of the equation to solve.
  *
  * \returns a solution.
  *
  * \note_about_checking_solutions
  *
  * \note_about_arbitrary_choice_of_solution
  *
  * Example: \include HouseholderQR_solve.cpp
  * Output: \verbinclude HouseholderQR_solve.out
  */
template<typename Rhs>
inline const Solve<HouseholderQR, Rhs>
solve(const MatrixBase<Rhs>& b) const
{
  eigen_assert(m_isInitialized && "HouseholderQR is not initialized.");
  return Solve<HouseholderQR, Rhs>(*this, b.derived());
}

/** This method returns an expression of the unitary matrix Q as a sequence of Householder transformations.
  *
  * The returned expression can directly be used to perform matrix products. It can also be assigned to a dense Matrix object.
  * Here is an example showing how to recover the full or thin matrix Q, as well as how to perform matrix products using operator*:
  *
  * Example: \include HouseholderQR_householderQ.cpp
  * Output: \verbinclude HouseholderQR_householderQ.out
  */
HouseholderSequenceType householderQ() const
{
  eigen_assert(m_isInitialized && "HouseholderQR is not initialized.");
  return HouseholderSequenceType(m_qr, m_hCoeffs.conjugate());
}

/** \returns a reference to the matrix where the Householder QR decomposition is stored
  * in a LAPACK-compatible way.
  */
const MatrixType& matrixQR() const
{
    eigen_assert(m_isInitialized && "HouseholderQR is not initialized.");
    return m_qr;
}

template<typename InputType>
HouseholderQR& compute(const EigenBase<InputType>& matrix) {
  m_qr = matrix.derived();
  computeInPlace();
  return *this;
}

/** \returns the absolute value of the determinant of the matrix of which
  * *this is the QR decomposition. It has only linear complexity
  * (that is, O(n) where n is the dimension of the square matrix)
  * as the QR decomposition has already been computed.
  *
  *
