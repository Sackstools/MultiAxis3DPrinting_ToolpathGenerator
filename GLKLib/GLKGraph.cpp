// GLKGraph.cpp: implementation of the GLKGraph class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "GLKGraph.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GLKGraph::GLKGraph()
{
	// Constructor for the GLKGraph class.
	// Initializes the node and edge lists by removing all elements.
	nodeList.RemoveAll();	edgeList.RemoveAll();
}

GLKGraph::~GLKGraph()
{
	// Destructor for the GLKGraph class.
	// Clears all nodes and edges before the object is destroyed.
	clearAll();
}

//////////////////////////////////////////////////////////////////////
// Graph manipulation methods
//////////////////////////////////////////////////////////////////////

void GLKGraph::_Debug() 
{
	// Debugging method for creating a sample graph and testing the minimum cut algorithm.
	// It creates nodes and edges, sets their weights, and computes the minimum cut.
	// It then prints the source region nodes.
	GLKGraphNode *node1;
	GLKGraphNode *node2;
	GLKGraphNode *node3;
	GLKGraphNode *node4;
	GLKGraphNode *node5;
	GLKGraphEdge *edge1;
	GLKGraphEdge *edge2;
	GLKGraphEdge *edge3;
	GLKGraphEdge *edge4;
	GLKGraphEdge *edge5;
	GLKGraphEdge *edge6;
	GLKGraphEdge *edge7;
	GLKObList srList,trList;

	node1=new GLKGraphNode;	AddNode(node1);
	node2=new GLKGraphNode;	AddNode(node2);
	node3=new GLKGraphNode;	AddNode(node3);
	node4=new GLKGraphNode;	AddNode(node4);
	node5=new GLKGraphNode;	AddNode(node5);

	edge1=new GLKGraphEdge;	edge1->startNode=node1;	edge1->endNode=node2; edge1->m_weight=12.0;
	AddEdge(edge1);
	edge2=new GLKGraphEdge;	edge2->startNode=node3;	edge2->endNode=node1; edge2->m_weight=14.0;
	AddEdge(edge2);
	edge3=new GLKGraphEdge;	edge3->startNode=node2;	edge3->endNode=node3; edge3->m_weight=5.0;
	AddEdge(edge3);
	edge4=new GLKGraphEdge;	edge4->startNode=node3;	edge4->endNode=node4; edge4->m_weight=8.0;
	AddEdge(edge4);
	edge5=new GLKGraphEdge;	edge5->startNode=node4;	edge5->endNode=node5; edge5->m_weight=10.0;
	AddEdge(edge5);
	edge6=new GLKGraphEdge;	edge6->startNode=node4;	edge6->endNode=node2; edge6->m_weight=7.0;
	AddEdge(edge6);
	edge7=new GLKGraphEdge;	edge7->startNode=node2;	edge7->endNode=node5; edge7->m_weight=16.0;
	AddEdge(edge7);

	FillInEdgeLinkersOnNodes();
	double maxFlow=MinimumCut(node1,node5,&srList,&trList,true);

	GLKPOSITION Pos;
	for(Pos=srList.GetHeadPosition();Pos!=NULL;) {
		GLKGraphNode *node=(GLKGraphNode *)(srList.GetNext(Pos));
		printf("Source region node: %p\n", node);
	}
}

double GLKGraph::MinimumCut(GLKGraphNode *sourceNode, GLKGraphNode *targetNode, 
							GLKObList *sourceRegionNodeList, GLKObList *targetRegionNodeList,
							bool bComputeMaxFlow)
{
	// Calculates the minimum cut of the graph between the source and target nodes.
	// If bComputeMaxFlow is true, it also computes the maximum flow.
	// It uses the Ford-Fulkerson algorithm with the Edmonds-Karp labeling algorithm.
	GLKObList linkList;
	GLKPOSITION Pos;

	_initializePreflow(sourceNode);

	linkList.RemoveAll();
	for(Pos=nodeList.GetHeadPosition();Pos!=NULL;) {
		GLKGraphNode *node=(GLKGraphNode *)(nodeList.GetNext(Pos));
		if (node==sourceNode) continue;
		if (node==targetNode) continue;
		linkList.AddTail(node);
	}

	int oldHeight;	GLKGraphNode *uNode;
	Pos=linkList.GetHeadPosition();
	while(Pos!=NULL) {
		uNode=(GLKGraphNode *)(linkList.GetAt(Pos));

		oldHeight=uNode->m_height;
		
		_discharge(uNode);
		
		if (uNode->m_height>oldHeight) {
			linkList.RemoveAt(Pos);
			linkList.AddHead(uNode);
			Pos=linkList.GetHeadPosition();
		}
		
		linkList.GetNext(Pos);
	}

	_partitionByResidualGraph(sourceNode,targetNode,sourceRegionNodeList,targetRegionNodeList);
	if (bComputeMaxFlow) return _computeMaxFlow();
	return 0.0;
}

void GLKGraph::_partitionByResidualGraph(GLKGraphNode *sourceNode, GLKGraphNode *targetNode, 
										 GLKObList *sourceRegionNodeList, 
										 GLKObList *targetRegionNodeList)
