// GLKHeap.h: interface for the GLKHeap class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _GLKHEAPNODE
#define _GLKHEAPNODE

// GLKHeapNode class represents a node in the heap. It inherits from GLKObject and contains
// an index, attached object, and value (weight). The index is used for locating the node in a heap,
// and the attached object is the one that updates the node's weight.
class GLKHeapNode : public GLKObject
{
public:
	GLKHeapNode() {index=0;}; // Default constructor initializes the index to 0
	virtual ~GLKHeapNode() {}; // Destructor

	float GetValue() {return v;}; // Returns the node's value (weight)
	void SetValue(float value) {v=value;}; // Sets the node's value (weight)

	int index; // Index for locating the node in a heap
	void* attachedObj; // Attached object that updates the node's weight

protected:
	float v; // Weight
};

#endif

#ifndef _GLKHEAP
#define _GLKHEAP

// GLKHeap class represents a heap data structure. It can be constructed with a maximum size and a flag
// to indicate whether it is a min or max heap. It contains methods for inserting, removing, and adjusting
// nodes in the heap, as well as utility functions for restoring the heap after insertion or deletion.
class GLKHeap  
{
public:
	GLKHeap(int maxsize, bool minOrMax=true); // Constructor with a maximum size and a flag to indicate min or max heap
	GLKHeap(int* arr, int n, bool minOrMax=true); // Constructor with an array and a flag to indicate min or max heap
	virtual ~GLKHeap(); // Destructor

	// Access operator to retrieve a node from the heap
	const GLKHeapNode* operator[] (int i);

	// Methods to retrieve the size, check if the heap is empty or full, and set or retrieve the min or max flag
	int ListSize();
	bool ListEmpty();
	bool ListFull();
	void SetKetOnMinOrMax(bool flag);
	bool IsKeyOnMinOrMax();

	// Methods to insert, remove, adjust, and clear nodes in the heap
	bool Insert(GLKHeapNode* item);
	GLKHeapNode* RemoveTop();
	GLKHeapNode* GetTop();
	void AdjustPosition(GLKHeapNode* item);
	void Remove(GLKHeapNode* item);
	void ClearList();

private:
	bool bMinMax; // Flag to indicate
