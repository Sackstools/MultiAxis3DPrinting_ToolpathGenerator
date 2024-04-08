// GLKGraph.h: interface for the GLKGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "GLKObList.h"

// Forward declaration of GLKGraphNode class to avoid circular dependency
#ifndef _GLKGRAPHNODE
#define _GLKGRAPHNODE

class GLKGraphNode : public GLKObject
{
public:
    // Default constructor
    GLKGraphNode() {
        // Initialize the edge list and attached object
        edgeList.RemoveAll();
        attachedObj = NULL;
        // Initialize the variables for minimum cut
        m_excess = 0.0;
        m_height = 0;
        nextNode = NULL;
    };

    // Default destructor
    virtual ~GLKGraphNode() {};

    // Attached object pointer
    void *attachedObj;

    // List of edges connected to this node
    GLKObList edgeList;

    // Variables for minimum cut
    double m_excess;
    int m_height;
    GLKGraphNode *nextNode;
};

// Define GLKGRAPHNODE to avoid redefinition
#endif

// Forward declaration of GLKGraphEdge class to avoid circular dependency
#ifndef _GLKGRAPHEDGE
#define _GLKGRAPHEDGE

class GLKGraphEdge : public GLKObject
{
public:
    // Default constructor
    GLKGraphEdge() {
        // Initialize the start node, end node, weight, and attached object
        startNode = NULL;
        endNode = NULL;
        m_weight = 0.0;
        attachedObj = NULL;
        // Initialize the variable for minimum cut
        m_flow = 0.0;
    };

    // Default destructor
    virtual ~GLKGraphEdge() {};

    // Pointers to the start and end nodes
    GLKGraphNode* startNode;
    GLKGraphNode* endNode;

    // Weight of the edge
    double m_weight;

    // Attached object pointer
    void *attachedObj;

    // Variable for minimum cut
    double m_flow;
};

// Define GLKGRAPHEDGE to avoid redefinition
#endif

// Forward declaration of GLKGraphCutNode class to avoid circular dependency
#ifndef _GLKGRAPH
#define _GLKGRAPH

class GLKGraphCutNode;

class GLKGraph  
{
public:
    // Default constructor
    GLKGraph();

    // Default destructor
    virtual ~GLKGraph();

    // Add a node to the graph
    void AddNode(GLKGraphNode *node);

    // Add an edge to the graph
    void AddEdge(GLKGraphEdge *edge);

    // Fill in the edge linkers on nodes
    void FillInEdgeLinkersOnNodes();

    // Debug function to print the graph
    void _Debug();

    // Minimum cut function
public:
    double MinimumCut(GLKGraphNode *sourceNode, GLKGraphNode *targetNode, 
                      GLKObList *sourceRegionNodeList, GLKObList *targetRegionNodeList, 
                      bool bComputeMaxFlow = false);

private:
    // Helper functions for minimum cut
    void _initializePreflow(GLKGraphNode *sourceNode);
    void _discharge(GLKGraphNode *uNode);
    void _push(GLKGraphNode *u
