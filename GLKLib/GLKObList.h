// GLKObList.h: interface for the GLKObList class.
// This header file defines the GLKObList class, which is a doubly linked list for managing objects.
// It provides methods for adding, removing, and accessing objects in the list.
//////////////////////////////////////////////////////////////////////

#include <../ThirdPartyDependence/Eigen/Dense> 

#ifndef _GLKObject
#define _GLKObject

// GLKObject class definition
// This is a simple class that serves as the data type for the GLKObNode class.
class GLKObject  
{
public:
	GLKObject () {};
	//int type;
};

#endif



#ifndef _GLKObNode
#define _GLKObNode

// GLKObNode class definition
// This class represents a node in the doubly linked list.
// Each node contains a pointer to the previous and next nodes, as well as a pointer to the data object.
class GLKObNode
{
public:
    GLKObNode(GLKObNode* ptrprev=nullptr,GLKObNode* ptrnext=nullptr)	{next=ptrnext;prev=ptrprev;};

	void InsertAfter(GLKObNode *p) {
		// Inserts the given node after this node
		GLKObNode *oldNextNode=next;
		next=p;p->prev=this;
		if (oldNextNode) {oldNextNode->prev=p;p->next=oldNextNode;}
	};
	GLKObNode *DeleteAfter() {
		// Deletes and returns the node after this node
        GLKObNode *tempObj=next;
        if (next==nullptr) return nullptr;
		next=tempObj->next;
		next->prev=this;
		return tempObj;
	};

	void InsertBefore(GLKObNode *p) {
		// Inserts the given node before this node
		GLKObNode *oldPrevNode=prev;
		prev=p;p->next=this;
		if (oldPrevNode) {oldPrevNode->next=p;p->prev=oldPrevNode;}
	};
	GLKObNode *DeleteBefore() {
		// Deletes and returns the node before this node
		GLKObNode *tempObj=prev;
        if (prev==nullptr) return nullptr;
		prev=tempObj->prev;
		prev->next=this;
		return tempObj;
	};

	GLKObNode *next;
	GLKObNode *prev;
	GLKObject *data;

};

#endif



#ifndef _GLKObList
#define _GLKObList

// GLKObList class definition
// This class represents a doubly linked list of GLKObNode objects.
// It provides methods for adding, removing, and accessing nodes in the list.
class GLKObList  
{
public:
	GLKObList();
	virtual ~GLKObList();

	GLKObject* GetHead();
	// Returns the data object of the first node in the list

	GLKObject* GetTail();
	// Returns the data object of the last node in the list

	GLKPOSITION GetHeadPosition() {return headPos;};
	GLKPOSITION GetTailPosition() {return tailPos;};
	// Returns the position of the first and last nodes in the list

	GLKPOSITION FindIndex(int index);
	// Returns the position of the node at the given index

	GLKPOSITION Find(GLKObject* element);
	// Returns the position of the node containing the given data object

	GLKPOSITION AddHead( GLKObject* newElement );
	// Adds a new node with the given data object to the beginning of the list

	void AddHead( GLKObList* pNewList );
	// Adds a new list to the beginning of this list

	GLKPOSITION AddTail( GLKObject* newElement );
	// Adds a new node with the given data object to the end of the list

	void AddTail( GLKObList* pNewList );
	// Adds a new list to the end of this list

	GLKObject* RemoveHead();
	// Removes and returns the first node in the list

	GLKObject* RemoveTail();
	// Removes and returns the last node in the list

	GLKObject* RemoveAt(GLKPOSITION rPosition);
	// Removes and returns the node at the given position

	void Remove(GLKObject* element);
	// Removes the first node containing the given data object

	void RemoveAll();
	// Removes all nodes from the list

	void RemoveAllWithoutFreeMemory();
	// Removes all nodes from the list without freeing memory

	GLKObject* GetNext( GLKPOSITION& rPosition );
	// Returns the data object of the next node in the list

	GLKObject* GetPrev( GLKPOSITION& rPosition );
	// Returns the data object of the previous node in the list

	GLKObject* GetAt( GLKPOSITION rPosition );
	// Returns the data object of the node at the given position

	GLKPOSITION InsertBefore( GLKPOSITION rPosition, GLKObject* newElement );
	// Inserts a new node with the given data object before the node at the given position

	GLKPOSITION InsertAfter
