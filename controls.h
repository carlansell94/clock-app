#ifndef CONTROLS_H
#define CONTROLS_H

#include "draw_text.h"
#include "scene.h"

enum ButtonType { RESET_BUTTON, MODE_BUTTON, START_STOP_BUTTON, NO_BUTTON };

inline Coordinate<double> getMouseCoordinate(int x, int y) {
    Coordinate<double> mouseCoordinate;
    GLfloat windowX, windowY, windowZ;
    GLdouble modelMatrix[16];
    GLdouble projectionMatrix[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX,
                 modelMatrix);  // Get modelview matrix values
    glGetDoublev(GL_PROJECTION_MATRIX,
                 projectionMatrix);        // Get projection matrix values
    glGetIntegerv(GL_VIEWPORT, viewport);  // Get viewport values

    windowX = (float)x;
    windowY = (float)viewport[3] - (float)y;  // Flip y coordinate

    glReadPixels(x, int(windowY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT,
                 &windowZ);  // Read data from pixel
    gluUnProject(
        windowX, windowY, windowZ, modelMatrix,
        projectionMatrix,  // Map coordinates of mouse click to 3d coordinates
        viewport, &(mouseCoordinate.x), &(mouseCoordinate.y),
        &(mouseCoordinate.z));

    return mouseCoordinate;
}

inline void drawMenuPrompt() {
    glDisable(GL_LIGHTING);
    drawText(10, 480, "Press 'm' to show menu");
    glEnable(GL_LIGHTING);
}

inline void drawMenu() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);

    drawText(10, 480, "CONTROLS");
    drawText(10, 461, "t: Switch between analogue and digital clocks");
    drawText(10, 442, "d: Switch date display on/off");
    drawText(10, 423, "+/-: Zoom in/out");
    drawText(10, 404, "Arrow Keys: Change camera position");
    drawText(10, 385, "r: Reset settings to default");
    drawText(10, 366, "q: Quit");

    drawText(10, 317, "ANALOGUE MODE ONLY");
    drawText(10, 298, "f: Change appearance of clock face");
    drawText(10, 279, "h: Change appearance of clock hands");
    drawText(10, 260, "w: Change width of clock hands");

    drawText(10, 211, "DIGITAL MODE ONLY");
    drawText(10, 192, "c: Change colour of time display");
    drawText(10, 173, "h: Switch between 12hr and 24hr mode (Default is 24hr)");

    drawText(
        10, 124,
        "Each clock includes the ability to run in 'stopwatch' mode. This is");
    drawText(
        10, 105,
        "operated using buttons on the clock itself. To enter stopwatch mode,");
    drawText(
        10, 86,
        "click the 'MODE' button located on the clock. To start and stop the");
    drawText(10, 67,
             "stopwatch, click the 'START' button. Reset the stopwatch using "
             "the 'RESET'");
    drawText(10, 48,
             "button. To switch back to 'time' mode, press the 'MODE' button.");
}

#endif
