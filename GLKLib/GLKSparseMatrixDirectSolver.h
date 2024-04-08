// GLKSparseMatrixDirectSolver.h: interface for the GLKSparseMatrixDirectSolver class.
// This header file defines the GLKSparseMatrixDirectSolver class, which provides
// functions for solving sparse matrix equations using direct methods.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GLKSPARSEMATRIX_DIRECT_SOLVER // Include guard to prevent multiple inclusions
#define _GLKSPARSEMATRIX_DIRECT_SOLVER

#include "GLKSparseMatrix.h" // Include the GLKSparseMatrix class header

class GLKSparseMatrixDirectSolver  
{
public:
    // Constructors and destructors
    GLKSparseMatrixDirectSolver();
    virtual ~GLKSparseMatrixDirectSolver();

    // Public static methods
    // BandGaussianElimination: Solves a sparse matrix equation using banded Gaussian elimination.
    // Parameters:
    //     sparseMatrix: A pointer to the sparse matrix to be solved.
    //     B: A double pointer to the right-hand side vector or matrix.
    // Returns:
    //     A boolean indicating success (true) or failure (false).
    static bool BandGaussianElimination(GLKSparseMatrix *sparseMatrix, double *B);
    static bool BandGaussianElimination(GLKSparseMatrix *sparseMatrix, int colNum, double **B);

private:
    // Private helper method
    // aband: A helper function for the BandGaussianElimination method.
    // Parameters:
    //     b: A double pointer to the input vector.
    //     d: A double pointer to the diagonal elements of the matrix.
    //     n: The size of the matrix.
    //     l: The lower bandwidth of the matrix.
    //     il: The index of the first nonzero diagonal element.
    //     m: The upper bandwidth of the matrix.
    // Returns:
    //     An integer indicating the pivot row.
    static int aband(double* b, double* d, long n, long l, long il, long m);
};

#endif
