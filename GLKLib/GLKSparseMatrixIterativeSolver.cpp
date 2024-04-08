// GLKSparseMatrixLib.cpp: implementation of the GLKSparseMatrixLib class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

#include "GLKSparseMatrix.h"
#include "GLKSparseMatrixIterativeSolver.h"

#define EPS		1.0e-8

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GLKSparseMatrixIterativeSolver::GLKSparseMatrixIterativeSolver()
// Default constructor for the GLKSparseMatrixIterativeSolver class.

{

}

GLKSparseMatrixIterativeSolver::~GLKSparseMatrixIterativeSolver()
// Destructor for the GLKSparseMatrixIterativeSolver class.

{

}

//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

void GLKSparseMatrixIterativeSolver::SparseMatrixIn_ZeroStartIndex(double **a, unsigned long n, double thresh, unsigned long nmax, 
									double *sa, unsigned long *ija)
// This function converts a given sparse matrix in the standard two-dimensional array format (a)
// to the sparse matrix format used in this library (sa and ija). The input matrix is expected to have
// zero-based indexing. The function stores the diagonal elements in sa and the off-diagonal elements in sa.
// It also stores the indices of the columns corresponding to the off-diagonal elements in ija.

{
	unsigned long i,j,k;

	for (j=1;j<=n;j++) sa[j]=a[j-1][j-1];	// Store diagonal elements.
	ija[1]=n+2;							// Index to 1st row off-diagonal element, if any.
	k=n+1;
	for (i=1;i<=n;i++) {				// Loop over rows.
		for (j=1;j<=n;j++) {			// Loop over columns.
			if (fabs(a[i-1][j-1]) >= thresh && i != j) {
	
