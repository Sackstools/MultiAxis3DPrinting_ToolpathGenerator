#include "GLKLib.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <math.h>

#ifndef _GLKCAMERATOOL
#define _GLKCAMERATOOL

// Enum defining different camera types
typedef enum camera_type {ORBIT,PAN,ZOOM,ORBITPAN,ZOOMWINDOW};

// GLKCameraTool class inherits from GLKMouseTool
class GLKCameraTool : public GLKMouseTool
{
public:
    // Constructor with two parameters: cView and camera type
    GLKCameraTool(GLKLib *cView, camera_type ct)
    {
        pView=cView;
        m_ct=ct;
        tool_type = 0;
    }

    // Destructor
    virtual ~GLKCameraTool() {};

    // Function to set camera type
    void setCameraType(camera_type ct) {m_ct = ct;}

    // Function to get camera type
    camera_type getCameraType() {return m_ct;}

private:
    GLKLib *pView; // Pointer to GLKLib object
    camera_type m_ct; // Current camera type
    QPoint lastPos; // Position of the last mouse event
    QPoint pt; // Temporary point variable

public:
    // Implementation of the process_event method
    virtual int process_event(QEvent *event, mouse_event_type event_type) {
        switch(m_ct) {
        case ORBITPAN:
            // Code for ORBITPAN camera type
            break;
        case ORBIT:
            // Code for ORBIT camera type
            break;
        case PAN:
            // Code for PAN camera type
            break;
        case ZOOM:
            // Code for ZOOM camera type
            break;
        case ZOOMWINDOW:
            // Code for ZOOMWINDOW camera type
            break;
        }
        return 0;
    }
};


#endif
