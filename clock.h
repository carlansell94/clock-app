#ifndef CLOCK_H
#define CLOCK_H

#include <GL/glut.h>

#include "characters.h"
#include "time.h"

class Clock {
   public:
    void resetButtonPressed() { resetStopwatch(); };

    void startButtonPressed() { toggleStopwatch(); };

    void modeButtonPressed() {
        disableStopwatch();
        resetStopwatch();
    };

    void drawDate(float t_red, float t_green, float t_blue) {
        std::string dateString = getDateString();
        glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(t_red, t_green, t_blue);
        glLineWidth(1.1f);
        glVertexPointer(2, GL_FLOAT, 0, letterPoints);
        glPushMatrix();
        glTranslatef(-0.32f, -0.26f, 0.01f);
        drawString(dateString);
        glPopMatrix();
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    virtual void display(bool t_showDate) = 0;

    virtual float* getButtonPositions() = 0;

    virtual void checkKeyPress(unsigned char key) = 0;

    virtual void reset() = 0;

    virtual ~Clock() = default;
};

#endif
