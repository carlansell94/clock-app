#ifndef HANDS_H
#define HANDS_H

#include <GL/glut.h>

#include <ctime>
#include <string>
#include <vector>

#include "time.h"

constexpr float clockFaceRadius = 0.9f;
constexpr float handLength = clockFaceRadius / 2.0f;
float handWidth = 3.0f;
int handStyle = 0;

const std::vector<std::vector<GLfloat>> handStyleVertices = {
    {0.0f, 0.0f, 0.0f, handLength},
    {0.0f, 0.0f, 0.0f, handLength, -0.03f, handLength - 0.05f, 0.0f, handLength,
     0.03f, handLength - 0.05f},
    {0.0f, 0.0f, -0.04f, handLength / 2, -0.02f, handLength - 0.5f, -0.04f,
     handLength - 0.55f, 0.0f, handLength, 0.04f, handLength - 0.55f, 0.02f,
     handLength - 0.5f, 0.04f, handLength / 2},
    {0.0f, 0.0f, -0.04f, handLength / 2, 0.0f, handLength, 0.04f,
     handLength / 2}};

inline void cycleHandStyle() {
    const int handStyleCount = handStyleVertices.size();
    handStyle++;

    if (handStyle == handStyleCount) {
        handStyle = 0;
    }
}

inline void drawHand(const float &t_angle, const float &t_zTranslate,
                     const float &t_scale = 1.0f) {
    const auto &selectedStyleVertices = handStyleVertices[handStyle];

    glPushMatrix();
    glScalef(t_scale, t_scale, 1.0f);
    glRotatef(t_angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, t_zTranslate);

    switch (handStyle) {
        case 0:
        case 1:
            glBegin(GL_LINE_STRIP);
            break;
        case 2:
        case 3:
            glBegin(GL_POLYGON);
            break;
        default:
            glBegin(GL_LINES);
            break;
    }

    for (size_t i = 0; i < selectedStyleVertices.size() - 1; i += 2) {
        glVertex2f(selectedStyleVertices[i], selectedStyleVertices[i + 1]);
    }

    glEnd();
    glPopMatrix();
}

const float handColour[9] = {
    1.0f, 0.0f, 0.0f,  // small hand
    0.0f, 1.0f, 0.0f,  // medium hand
    0.0f, 0.0f, 1.0f   // large hand
};

inline void drawMediumHand(const int &t_major, const int &t_minor) {
    const float angle = 360 - (6 * t_major) - (0.1f * t_minor);
    glColor3f(handColour[3], handColour[4], handColour[5]);
    drawHand(angle, 0.02f, 1.6f);
}

inline void drawShortHand(const float &t_major, const int &t_minor) {
    const float angle = 360 - (30 * t_major) - (0.5f * t_minor);
    glColor3f(handColour[0], handColour[1], handColour[2]);
    drawHand(angle, 0.01f);
}

inline void drawLargeHand(const int &t_major) {
    glColor3f(0.0f, 0.0f, 1.0f);
    float angle = 360 - 6 * t_major;
    drawHand(angle, 0.03f, 1.9f);
}

inline void drawStopWatchHands() {
    std::string displayTime = getStopwatchTimeString();
    const int minutes = std::stoi(displayTime.substr(0, 2));
    const int seconds = std::stoi(displayTime.substr(2, 2));
    const int milliseconds = std::stoi(displayTime.substr(4, 2));

    drawShortHand((float)minutes / 5, seconds / 5);
    drawMediumHand(seconds, milliseconds * 60 / 100);
    drawLargeHand(milliseconds * 60 / 100);  // Draw hand to display ms
}

inline void drawClockHands() {
    struct tm *strtime = getCurrentTime();
    drawShortHand(strtime->tm_hour, strtime->tm_min);
    drawMediumHand(strtime->tm_min, strtime->tm_sec);
    drawLargeHand(strtime->tm_sec);

    glPointSize(handWidth * 3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.04f);
    glEnd();
}

#endif
