#include "heatMethod.h"
#include <iostream>

using namespace std;
using namespace Eigen;

// Constructor for the heatMethod class, initializes the surface mesh and detects the genus of the mesh
heatMethod::heatMethod(QMeshPatch* inputMesh)
{
    surfaceMesh = inputMesh;
    int genus = detectGenus();
}

// Destructor for the heatMethod class
heatMethod::~heatMethod() {}

////////////////////////////////
/* Heat method basic function */

// Computes the boundary heat kernel using the initialized boundary heat kernel and runs the heat method
void heatMethod::compBoundaryHeatKernel() {
    _initBoundaryHeatKernel();
    runHeatMethod();

    // After computation, installs the geo-Field to boundary field
    for (GLKPOSITION Pos = surfaceMesh->GetNodeList().GetHeadPosition(); Pos;) {
        QMeshNode* Node = (QMeshNode*)surfaceMesh->GetNodeList().GetNext(Pos);
        Node->boundaryValue = Node->geoFieldValue;
    }

    printf("-- (heatMethodField) Finish compute boundary heat kernel !\n\n");
}

// Initializes the boundary heat kernel by setting the boundary points as heat sources and selecting them
void heatMethod::_initBoundaryHeatKernel() {
    for (GLKPOSITION Pos = surfaceMesh->GetNodeList().GetHeadPosition(); Pos;) {
        QMeshNode* Node = (QMeshNode*)surfaceMesh->GetNodeList().GetNext(Pos);
        Node->selected = false; Node->geoFieldValue = 0;
    }

    // Set boundary point as heat source
    for (GLKPOSITION Pos = surfaceMesh->GetEdgeList().GetHeadPosition(); Pos;) {
        QMeshEdge* edge = (QMeshEdge*)surfaceMesh->GetEdgeList().GetNext(Pos);
        if (edge->IsBoundaryEdge() == true) {
            edge->GetStartPoint()->geoFieldValue = 1; edge->GetEndPoint()->geoFieldValue = 1;
            edge->GetStartPoint()->selected = true; edge->GetEndPoint()->selected = true;
        }
    }

    // Select two points as heat sources
    /*for (GLKPOSITION Pos = surfaceMesh->GetNodeList().GetHeadPosition(); Pos;) {
        QMeshNode* Node = (QMeshNode*)surfaceMesh->GetNodeList().GetNext(Pos);
        if (Node->GetIndexNo() == 0 || Node->GetIndexNo() == 300) {
            Node->selected = true; Node->geoFieldValue = 1;
        }
    }*/
}

// Runs the heat method by initializing the mesh index, creating the Laplacian matrix, and solving the heat equation
void heatMethod::runHeatMethod() {

    this->initialMeshIndex();

    VectorXd u(surfaceMesh->GetNodeNumber());
    u.setZero();

    int index = 0;
    for (GLKPOSITION Pos = surfaceMesh->GetNodeList().GetHeadPosition(); Pos;) {
        QMeshNode* Node = (QMeshNode*)surfaceMesh->GetNodeList().GetNext(Pos);
        u(index) = Node->geoFieldValue;
        index++;
    }

    heatMethodPreProcess();
    heatMethodCompwithConstrain(u);
}

// Performs preprocessing for the heat method by building the Laplacian matrix, area matrix, and computing the mean edge length
void heatMethod::heatMethodPreProcess() {

    int v = surfaceMesh->GetNodeNumber();

    // Build Laplacian Matrix
    Eigen::SparseMatrix<double> L(v, v);
    this->buildLaplacian(L, false);

    poissonSolver.compute(L);

    // Build Area Matrix
    Eigen::SparseMatrix<double> A(v, v);
    this->buildAreaMatrix(A);

    double mean_edge_length = meanEdgeLength();

    t = mean_edge_length * mean_edge_length;

    F = A - t * L;

    heatSolver.compute(F);
}

// Computes the heat equation with constraints by solving the equation and computing the unit vector field X and divergence ∇.X
void heatMethod::heatMethodCompwithConstrain(Eigen::VectorXd& u) {

    u = heatSolver.solve(u);

    // compute unit vector field X and divergence ∇.X
    Eigen::MatrixXd gradients(surfaceMesh->GetFaceNumber(), 3);
    this->computeVectorField(gradients, u);
    //cout << gradients << endl;

    Eigen::VectorXd integratedDivs(surfaceMesh->GetNodeNumber());
    this->computeIntegratedDivergence(integratedDivs, gradients);
    //cout << integratedDivs << endl;

    /*build the equation with constrain*/
    int vc = surfaceMesh->GetNodeNumber(); //constrained node number
    for (GLKPOSITION Pos = surfaceMesh->GetNodeList().GetHeadPosition(); Pos;) {
        QMeshNode* Node = (QMeshNode*)surfaceMesh->GetNodeList().GetNext(Pos);
        if (Node->selected) vc--;
    }
    Eigen::VectorXd integratedDivs_constrain(vc); int Cindex = 0; int index = 0;
    for (GLKPOSITION Pos = surfaceMesh->GetNodeList().GetHeadPosition(); Pos;) {
        QMeshNode* Node = (QMeshNode*)surfaceMesh->GetNodeList().GetNext(Pos);
        if (Node->selected) index++;
        else {
            integratedDivs_constrain(Cindex) = integratedDivs(index);
            Cindex++; index++;
        }
    }

    Eigen::SparseMatrix<double> L(vc, vc);
    buildLaplacian(L, true);
    index = 0;
    for (GLKPOSITION Pos = surfaceMesh->GetNodeList().GetHeadPosition(); Pos;) {
        QMeshNode* Node = (QMeshNode*)surfaceMesh->GetNodeList().Get
