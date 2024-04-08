/*
HeatMethod.h
Heat method field value computing

Written by Guoxin Fang on 08-15-2020 (last updated)
*/

#ifndef HEATMETHOD_H
#define HEATMETHOD_H

#include "PolygenMesh.h" // Include the PolygenMesh header file
#include "../GLKLib/GLKObList.h" // Include the GLKObList header file
#include "..\ThirdPartyDependence\Eigen\Eigen" // Include the Eigen header file

class heatMethod
{
public:
    // Constructor for the heatMethod class
    heatMethod(QMeshPatch* inputMesh);
    ~heatMethod(); // Destructor for the heatMethod class

    // Method to compute the boundary heat kernel
    void compBoundaryHeatKernel();

    // Main method to run the heat method
    void runHeatMethod();
    // Method for mesh refinement
    void meshRefinement();

private:
    // Pointer to the input mesh
    QMeshPatch* surfaceMesh;

    // Eigen matrices for the heat method
    Eigen::SparseMatrix<double> L;
    Eigen::SparseMatrix<double> A;
    double t;
    Eigen::SparseMatrix<double> F;
    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> poissonSolver;
    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> heatSolver;

    // Private methods for the heatMethod class
    void _initBoundaryHeatKernel();

    // Helper methods for the heat method
    int detectGenus();
    void initialMeshIndex();
    void heatMethodPreProcess();
    void heatMethodCompwithConstrain(Eigen::VectorXd& u);

    // Methods to build matrices for the heat method
    void buildLaplacian(Eigen::SparseMatrix<double>& L, bool constrain) const;
    void buildAreaMatrix(Eigen::SparseMatrix<double>& A) const;
    // Methods to compute gradients and divergence
    void computeVectorField(Eigen::MatrixXd& gradients, const Eigen::VectorXd& u) const;
    void computeIntegratedDivergence(Eigen::VectorXd& integratedDivs,
        const Eigen::MatrixXd& gradients
