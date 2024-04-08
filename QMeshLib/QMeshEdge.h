// QMeshEdge.h: interface for the QMeshEdge class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _QMESHEDGE
#define _QMESHEDGE

#include "../GLKLib/GLKObList.h"

class QMeshPatch;
class QMeshNode;
class QMeshFace;

class QMeshEdge : public GLKObject  
{
public:
    // Constructors and destructors
    //--------------------------------
    QMeshEdge();
    virtual ~QMeshEdge();

public:
    // Attribute flag manipulation functions
    //---------------------------------------
    bool GetAttribFlag(const int whichBit);
    void SetAttribFlag(const int whichBit, const bool toBe = true);

    // Index-related functions
    //-------------------------
    int GetIndexNo();		//from 1 to n
    void SetIndexNo(const int _index = 1);

    // Boundary edge identification function
    //---------------------------------------
    bool IsBoundaryEdge();

    // Start and end point access functions
    //--------------------------------------
    QMeshNode * GetStartPoint();
    void SetStartPoint(QMeshNode *_pStartPoint = nullptr);

    QMeshNode * GetEndPoint();
    void SetEndPoint(QMeshNode *_pEndPoint = nullptr);

    // Left and right face access functions
    //-------------------------------------
    QMeshFace * GetLeftFace();
    void SetLeftFace(QMeshFace *_pLeftFace = nullptr);

    QMeshFace * GetRightFace();
    void SetRightFace(QMeshFace *_pRightFace = nullptr);

    // Mesh patch pointer management functions
    //----------------------------------------
    void SetMeshPatchPtr(QMeshPatch* _mesh);
    QMeshPatch* GetMeshPatchPtr();

    // Normal calculation function
    //-----------------------------
    void CalNormal(double normal[]);

    // Sharp factor manipulation functions
    //-------------------------------------
    void SetSharpFactor(int factor);
    int GetSharpFactor();

    // Length and 2D length calculation functions
    //--------------------------------------------
    double CalLength();
    double GetLength();
    double Cal2DLength();
    double Get2DLength();

    // Attached list access function
    //-------------------------------
    GLKObList& GetAttachedList();

private:
    // Index and flag variables
    //--------------------------
    int indexno;
    bool flags[8];

    // Start and end point pointers
    //------------------------------
    QMeshNode *pStartPoint;
    QMeshNode *pEndPoint;

    // Left and right face pointers
    //-----------------------------
    QMeshFace *pLeftFace;
    QMeshFace *pRightFace;

    // Mesh patch pointer
    //--------------------
    QMeshPatch *meshSurface;

    // Attached object list
    //---------------------
    GLKObList attachedList;

    // Sharp factor and length variables
    //-----------------------------------
    int m_sharpFactor;
    double m_edgeLength, m_edge2DLength;

    // Triangle face list (for volume mesh)
    //-------------------------------------
    GLKObList FaceList;

public:
    // Triangle face list access function
    //-----------------------------------
    GLKObList& GetFaceList();

    // Additional variables
    //---------------------
    bool isConnectEdge;
    int refineNodeIndex;

};

#endif
