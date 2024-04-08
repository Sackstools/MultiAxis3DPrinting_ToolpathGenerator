// Typedefs for unary operations on matrices
typedef CwiseUnaryOp<internal::scalar_abs_op<Scalar>, const Derived> AbsReturnType;
// ... various other typedefs for unary operations ...

/**
  * \returns an expression of the coefficient-wise absolute value of \c *this
  *
  * Example: \include Cwise_abs.cpp
  * Output: \verbinclude Cwise_abs.out
  *
  * \sa <a href="group__CoeffwiseMathFunctions.html#cwisetable_abs">Math functions</a>, abs2()
  */
EIGEN_DEVICE_FUNC
EIGEN_STRONG_INLINE const AbsReturnType
abs() const
{
  return AbsReturnType(derived());
}

// Other unary operation functions follow a similar pattern, with example code and a sa link
// to the list of math functions.
