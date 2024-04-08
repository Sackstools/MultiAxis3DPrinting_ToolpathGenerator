#ifndef TOOLPATHGENERATION_H
#define TOOLPATHGENERATION_H

#include "QMeshPatch.h"
#include "PolygenMesh.h"
#include "QMeshNode.h"
#include "QMeshEdge.h"
#include "QMeshFace.h"
#include "../GLKLib/GLKObList.h"

class toolPathGeneration
{
public:
    // Constructor for the toolPathGeneration class
    toolPathGeneration(QMeshPatch* inputMesh);

    // Destructor for the toolPathGeneration class
    ~toolPathGeneration();

    // Generate a zigzag tool path
    void generateZigzagToolPath(PolygenMesh* tPath, int Num);

    // Generate a boundary tool path
    void generateBundaryToolPath(PolygenMesh* tPath, int Num, double offset);

    // Resample the tool path
    void resampling(PolygenMesh* tPath);

    // Automatically compute the number of tool path nodes
    int autoComputeTPathNum(bool type);

    // Automatically compute the zigzag tool path offset value
    double autoComputeZigZagTPathOffestingValue(
        int zigzagTPathNum, int boundaryTPathNum, double boundaryTPathOffset);

    // Merge field data for CCF
    void mergeFieldforCCF();

    // Member variables
    double minBoundaryFieldValue;
    double maxGapDist;
    double maxConnectDist;
    double boundaryGapDist;
    double toolpathOffset;

    bool breakZigzagbyBoundary;

private:
    // List of zigzag tool path iso-nodes
    GLKObList zigzagPathList;

    // List of boundary tool path iso-nodes
    GLKObList boundPathList;

    // Connection between iso-nodes and surface mesh edges (zigzag)
    Eigen::MatrixXi edgePIndex;

    // Connection between iso-nodes and surface mesh edges (boundary)
    Eigen::MatrixXi edgeBPIndex;

    // Surface mesh
    QMeshPatch* surfaceMesh;

    // Resampling length
    double resamplingLength;

    // Minimum number of zigzag tool path nodes
    int minZigZagtoolpathNodeNum;

    // Initialize the tool path generation
    void initialize(int Num);
    void initialize(int Num, double offset);

    // Functions for zigzag tool path generation
    bool generateZigZagIsoNode(int Num);

    bool generateSingleZigzagToolPathIsoNode(QMeshPatch* singlePath, double isoValue);
    void connectZigZagToolPathToRegion(PolygenMesh* tPath);
    QMeshNode* connectSingleZigZagToolPathandGenerateEdge(
        QMeshNode* startNode, QMeshNode *edgeSNode, QMeshPatch* tPathRegion, QMeshPatch* thisTPath, double endPointPos[]);

    // Functions for boundary tool path generation
    void generateBoundaryIsoNode(int Num, double offset);

    void generateSingleBoundaryToolPathIsoNode(QMeshPatch* singlePath, double isoValue);
    void buildOutRingToolPathandConnectZigzagPath(PolygenMesh* tPath);
    void buildOutRingToolPath_without_ConnectZigzagPath(PolygenMesh* tPath);

    void generateSingleBoundaryToolPath(PolygenMesh* tPath, double isoValue);
    QMeshNode* buildOneRingBoundaryToolPath(QMeshNode* startNode, QMeshNode*sNode, QMeshPatch* patch, QMeshPatch* boundIsoPatch);
    QMeshNode* findNextBoundaryToolPath(QMeshNode* startNode, QMeshPatch* boundIsoPatch);
    QMeshNode* findNextNearestPoint(QMeshNode* startNode, QMeshPatch* boundIsoPatch);

    // Other assistant functions
    double computeAverageConnectEdgeLength(QMeshPatch* patch);
    double resamplingSinglePatch(QMeshPatch* patch);

    // Other assistant functions
    bool detectSingleZigZagToolPathisProcessed(QMeshPatch* singlePath);
    bool detectAllZigZagToolPathisProcessed();
    bool detectAllBoundaryToolPathisProcessed();

    QMeshNode* buildNewNodetoQMeshPatch(QMeshPatch* patch, double pp[], double normal[]);
    QMeshEdge* buildNewEdgetoQMeshPatch(QMeshPatch* patch, QMeshNode* startNode, QMeshNode* endNode);

    bool runBreakingChecking(double firstCurve_IsoValue, double minBoundaryFieldValue);
};

#endif // TOOLPATHGENERATION_H
