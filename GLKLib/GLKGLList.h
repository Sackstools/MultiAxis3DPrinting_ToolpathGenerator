// GLKGLList.h: interface for the GLKGLList class.
// This header file declares the GLKGLList class, which is derived from the GLKObject class.
// The GLKGLList class is intended to be used for managing and rendering OpenGL objects.
//////////////////////////////////////////////////////////////////////

#ifndef _GLKGLLIST // Include guard to prevent multiple inclusions of this header file
#define _GLKGLLIST

#include "GLKLib.h" // Include GLKLib.h for required functionality
#include "GLKObList.h" // Include GLKObList.h for required functionality

class GLKGLList : public GLKObject // Declare GLKGLList as a class derived from GLKObject
{
public:
    // Default constructor for GLKGLList class
    GLKGLList() {};

    // Destructor for GLKGLList class
    virtual ~GLKGLList() {};

    // A virtual function to draw the OpenGL objects managed by this class
    // This function takes a GLKLib pointer as an argument, which represents the OpenGL view
    virtual void draw(GLKLib *view) {};
};

#endif  // Include guard
