// InteractiveTool.h

/**
 * @file InteractiveTool.h
 * @brief Header file for the InteractiveTool class.
 * @details This file contains the declaration of the InteractiveTool class, which is a derived class from GLKMouseTool.
 * The class is used to handle mouse events for selecting nodes, edges, faces, fixed points, and handles in a 3D scene.
 */

#ifndef INTERACTIVETOOL_H
#define INTERACTIVETOOL_H

#include "GLKLib.h" // Include GLKLib library
#include <QPoint> // Include QPoint class from the Qt GUI library

/**
 * @enum select_type
 * @brief Enum to represent the type of selection.
 * The enum has the following values:
 * - NODE: Select nodes
 * - EDGE: Select edges
 * - FACE: Select faces
 * - FIX: Select fixed points
 * - NHANDLE: Select handles
 */
typedef enum select_type { NODE, EDGE, FACE, FIX, NHANDLE };

/**
 * @class InteractiveTool
 * @brief Class to handle mouse events for selecting nodes, edges, faces, fixed points, and handles in a 3D scene.
 * The class is derived from GLKMouseTool and has methods to process mouse events and select nodes, edges, faces, fixed points, and handles.
 */
class InteractiveTool : public GLKMouseTool
{
public:
    /**
     * @brief Constructor for the InteractiveTool class with a QMeshPatch.
     * @param pGLKLib Pointer to the GLKLib object.
     * @param meshPatch_ Pointer to the QMeshPatch object.
     * @param mouseTool Pointer to the GLKMouseTool object.
     * @param selectType The type of selection.
     * @param Select True if the tool is used for selection, false otherwise.
     */
    InteractiveTool(GLKLib *pGLKLib, QMeshPatch *meshPatch_, GLKMouseTool *mouseTool, select_type selectType, bool Select);

    /**
     * @brief Constructor for the InteractiveTool class with a GLKObList.
     * @param pGLKLib Pointer to the GLKLib object.
     * @param polygenMeshList Pointer to the GLKObList object.
     * @param mouseTool Pointer to the GLKMouseTool object.
     * @param selectType The type of selection.
     * @param Select True if the tool is used for selection, false otherwise.
     */
    InteractiveTool(GLKLib *pGLKLib, GLKObList *polygenMeshList, GLKMouseTool *mouseTool, select_type selectType, bool Select);

    /**
     * @brief Destructor for the InteractiveTool class.
     */
    virtual ~InteractiveTool();

    /**
     * @brief Process mouse events and handle the selection.
     * @param event Pointer to the QEvent object.
     * @param event_type The type of mouse event.
     * @return The result of the event processing.
     */
    virtual int process_event(QEvent *event, mouse_event_type event_type);

    /**
     * @brief Get the type of selection.
     * @return The type of selection.
     */
    select_type getSelectedType() {return type;};

private:
    GLKLib *pGLK; // Pointer to the GLKLib object
    QMeshPatch *meshPatch; // Pointer to the QMeshPatch object
    GLKObList *polygenList; // Pointer to the GLKObList object
    select_type type; // The type of selection
    GLKMouseTool *mouse_tool; // Pointer to the GLKMouseTool object

    QPoint lastPos; // The last position of the mouse cursor
    QPoint pos;
