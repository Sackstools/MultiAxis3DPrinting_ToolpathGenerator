// GLKNearestNeighbor.h: interface for the GLKNearestNeighbor class.
// This header file defines the GLKNearestNeighbor class, which is used for finding the nearest neighbor in a set of points.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GLKNEAREST_NEIGHBOR
#define _GLKNEAREST_NEIGHBOR

#include "GLKObList.h" // Include GLKObList header file

class GLKNearestNeighborNode : public GLKObject // GLKNearestNeighborNode class inherits from GLKObject class
{
public:
	float m_pos[3]; // Array of 3 floats to store the position of the node
	int m_index; // Index of the node
	GLKPOSITION m_PosInGLKObList; // Position of the node in the GLKObList
};

class GLKNearestNeighbor // GLKNearestNeighbor class
{
public:
	GLKNearestNeighbor(int pntNum, float* xpos, float *ypos, float *zpos); // Constructor with 4 parameters
	GLKNearestNeighbor(int pntNum, float** pnts); // Overloaded constructor with 3 parameters
	virtual ~GLKNearestNeighbor(); // Destructor

	void PntsInRange(float queryPnt[], float range, GLKArray* indexArray); // Function to find points within a certain range of a query point
	void MovePnt(int pntIndex, float xNewPos, float yNewPos, float zNewPos); // Function to move a point to a new position

private:
	int m_xNum,m_yNum,m_zNum; // Integer variables to store the number of points in each dimension
	float m_size,m_xmin,m_ymin,m_zmin,m_xmax,m_ymax,m_zmax; // Floating point variables to store the size and range of the points
	GLKObList ****m_grids; // 4D array of GLKObList objects


