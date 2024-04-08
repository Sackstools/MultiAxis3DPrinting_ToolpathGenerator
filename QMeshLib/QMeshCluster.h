// QMeshCluster.h

// A class representing a mesh cluster, which is a collection of faces, nodes, and edges.
// Inherits from GLKObject, which provides basic object functionality.
class QMeshCluster : public GLKObject
{
public:
    // Constructor
    QMeshCluster();

    // Destructor
    virtual ~QMeshCluster();

public:

    // Returns the index number of the cluster (from 1 to n).
    int GetIndexNo();

    // Sets the index number of the cluster (from 1 to n).
    void SetIndexNo(const int _index = 1);

    // Returns the number of faces in the cluster.
    int GetClusterFaceNumber();

    // Returns the number of nodes in the cluster.
    int GetClusterNodeNumber();

    // Returns the number of edges in the cluster.
    int GetClusterEdgeNumber();

    // Returns a pointer to the cluster face record with the given index (from 1 to n).
    QMeshFace* GetClusterFaceRecordPtr(int No);

    // Returns a pointer to the cluster node record with the given index (from 1 to n).
    QMeshNode* GetClusterNodeRecordPtr(int No);

    // Returns a pointer to the cluster edge record with the given index (from 1 to n).
    QMeshEdge* GetClusterEdgeRecordPtr(int No);

    // Returns a reference to the list of cluster faces.
    GLKObList& GetClusterFaceList();

    // Returns a reference to the list of cluster nodes.
    GLKObList& GetClusterNodeList();

    // Returns a reference to the list of cluster edges.
    GLKObList& GetClusterEdgeList();

    // Returns a reference to the list of cluster boundary curves.
    GLKObList& GetBndCurveList();

    // Returns a reference to the list of cluster anchor nodes.
    GLKObList& GetAnchorNodeList();

    // A pointer to the centroid face of the cluster.
    QMeshFace* centroidFace;

private:
    // The index number of the cluster (from 1 to n).
    int indexno;

    // A list of cluster faces.
    GLKObList clusterFaceList;

    // A list of cluster nodes.
    GLKObList clusterNodeList;

    // A list of cluster edges.
    GLKObList clusterEdgeList;

    // A list of cluster anchor nodes.
    GLKObList clusterAnchorNodeList;

    // A list of cluster boundary curves.
    GLKObList clusterBndCurveList;
};

// A class representing a mesh cluster boundary curve, which is a collection of edges.
// Inherits from GLKObject, which provides basic object functionality.
class QMeshClusterBndCurve : public GLKObject
{
public:
    // Constructor
    QMeshClusterBndCurve();

    // Destructor
    virtual ~QMeshClusterBndCurve();

public:

    // Returns a pointer to the list of edges in the boundary curve.
    GLKObList* GetEdgeList();

    // Sets the left cluster of the boundary curve.
    void SetLeftCluster(QMeshCluster* cluster);

    // Returns a pointer to the left cluster of the boundary curve.
    QMeshCluster* GetLeftCluster();

    // Sets the right cluster of the boundary curve.
    void SetRightCluster(QMeshCluster* cluster);

    // Returns a pointer to the right cluster of the boundary curve
