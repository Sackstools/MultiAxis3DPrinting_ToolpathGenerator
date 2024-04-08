// GLKMatrixLib.h: interface for the GLKMatrixLib class.
// This header file defines the GLKMatrixLib class, which provides various matrix operations.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GLKMATRIXLIB
#define _GLKMATRIXLIB


class GLKMatrix
{
public:
	// Default constructor initializes the matrix with no rows and columns
	GLKMatrix() { mat = 0; m = 0; n = 0; };

	// Constructor with parameters initializes the matrix with specified number of rows and columns
	GLKMatrix(int _m, int _n);

	// Destructor deallocates memory used by the matrix
	~GLKMatrix();

	// CreateMatrix creates a matrix with specified number of rows and columns
	void CreateMatrix(int _m, int _n);

	// DeleteMatrix deallocates memory used by the matrix
	void DeleteMatrix();

	// Overloaded operators for matrix manipulation
	double& operator()(const int& i, const int& j) { return mat[i][j]; }
	double* operator[](const int& i) { return mat[i]; }
	operator double**() const { return mat; }
	GLKMatrix& operator=(const GLKMatrix &rhs);
	GLKMatrix& operator=(const double &rhs);
	GLKMatrix& operator=(double **rhs);
	GLKMatrix operator+(GLKMatrix & rhs);
	GLKMatrix operator*(const double &rhs);
	GLKMatrix operator/(const double &rhs);
	GLKMatrix& operator+=(GLKMatrix &rhs);
	GLKMatrix& operator*=(const double &rhs);

	// Functions to get matrix properties
	void PrintElements();
	int getRowNumber() { return m; };
	int getColumnNumber() { return n; };

private:
	double **mat; // Pointer to the matrix data
	int m, n; // Number of rows and columns in the matrix
};

class GLKMatrixLib  
{
public:
	// Default constructor
	GLKMatrixLib();

	// Destructor
	virtual ~GLKMatrixLib();

	// Static functions for matrix operations
	static void CreateMatrix(double** &a, int row, int col);
	static void DeleteMatrix(double** &a, int row, int col);
	static void CreateMatrix(bool** &a, int row, int col);
	static void DeleteMatrix(bool** &a, int row, int col);

	static void Mul(double**a /*m by n*/, double**b  /*n by k*/, int m, int n, int k, 
					double**c /*m by k*/);
	static void Mul(double**a /*m by n*/, double*b  /*n rows*/, int m, int n, 
					double*c /*m rows*/);
	static int Rank(double**a /*m by n*/, int m, int n);
	static bool Inverse(double**a, int n);
	static bool Pseudoinverse(double** inputMatrix, int row, int col, 
								double** outputMatrix /* with (col x row) */);
	static void SwitchCol(double** a, int row, int col, int colIndex1, int colIndex2);
	static void SwitchRow(double** a, int row, int col, int rowIndex1, int rowIndex2);
	static void Transpose(double** inputMatrix, int row, int col, 
							double** outputMatrix /* with (col x row) */);
	static void Transpose(double** inputMatrix, int n);

	static bool GaussSeidelSolver(double** a, double* b, int n, double* x, double eps);
	static void ConjugateGradientSolver(double** a, double* b, int n, double* x, double eps);

	static bool GaussJordanElimination(double** a, int n, double* b);
	static bool GaussJordanElimination(double** a, int n, double** b, int m);
	// Linear equation solution by Gauss-Jordan elimination. a[0...(n-1)][0...(n-1)]
	//	is the input matrix. b[0...(n-1)][0...(m-1)] is input containing the m right-hand side vectors. 
	// On output, a is replaced by its matrix inverse, and b is replaced by the corresponding 
	//	set of solution vectors.

	static bool CholeskyDecompositionSolver(double** a, int n, double* b);
	static bool CholeskyDecompositionSolver(double** a, int n, double** b, int m);
	// Positive-Definite Symmetric Linear Equation solution by Cholesky Decomposition. 
	//	a[0...(n-1)][0...(n-1)]	is the input positive-definite matrix. 
	//	b[0...(n-1)][0...(m-1)] is input containing the m right-hand side vectors. 
	// On output, a is replaced by its matrix inverse, and b is replaced by the corresponding 
	//	set of solution vectors.

	static bool SingularValueDecomposition(double**a /*m by n*/, int m, int n, 
					double**u /*m by m*/, double**v /*n by n*/, double eps=0.000001);
	//  A = U W VT  - where U is stored in **u
	//					    VT is stored in **v
	//						W is stored in a[i][i] by the descending order
    // Analytic solution for 2x2 and 3x3 singular value decomposition
        // as well as analytic solution for 2x2 and 3x3 matrix inverse
    static bool SingularValueDecomposition_2by2(double** a, double** u, double** v);
    static bool EigenDecomposition_2by2(double ATA[2][2], double& eigen
