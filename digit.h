#ifndef DIGIT_H
#define DIGIT_H

#include <GL/glut.h>

#include "coordinate.h"
#include "materials.h"
#include "time.h"

struct Transform {
    float x;
    float y;
    float rotation;
};

// Coordinates to define a single segment
Coordinate<float> segment[6] = {
    {-1.0f, 6.5f, 0.0f}, {0.0f, 7.5f, 0.0f},  {1.0f, 6.5f, 0.0f},
    {1.0f, -6.5f, 0.0f}, {0.0f, -7.5f, 0.0f}, {-1.0f, -6.5f, 0.0f},
};

// x offset of each segment
const float digitLocations[6] = {-0.66f, -0.44f, -0.16f, 0.06f, 0.34f, 0.56f};

// Define lit/unlit segments per digit
const bool segmentState[10][7] = {
    {1, 1, 1, 0, 1, 1, 1},  // 0
    {0, 0, 0, 0, 0, 1, 1},  // 1
    {0, 1, 1, 1, 1, 1, 0},  // 2
    {0, 0, 1, 1, 1, 1, 1},  // 3
    {1, 0, 0, 1, 0, 1, 1},  // 4
    {1, 0, 1, 1, 1, 0, 1},  // 5
    {1, 1, 1, 1, 1, 0, 1},  // 6
    {0, 0, 1, 0, 0, 1, 1},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 0, 1, 1, 1, 1, 1},  // 9
};

// Position of each segment in a single digit
Transform segments[7] = {{-8.0f, 8.5f, 0.0f},   {-8.0f, -8.5f, 0.0f},
                         {17.0f, 0.0f, 90.0f},  {0.0f, 0.0f, 90.0f},
                         {-17.0f, 0.0f, 90.0f}, {8.0f, 8.5f, 0.0f},
                         {8.0f, -8.5f, 0.0f}};

Coordinate<float> clockPoints[4] = {
    {-0.3f, 0.05f},   // Upper left LED
    {-0.3f, -0.05f},  // Lower left LED
    {0.2f, 0.05f},    // Upper middle LED
    {0.2f, -0.05f}    // Lower middle LED
};

Coordinate<float> stopwatchPoints[3] = {
    {-0.3f, 0.05f},   // Upper left LED
    {-0.3f, -0.05f},  // Lower left LED,
    {0.2f, -0.17f}    // Lower middle LED
};

Coordinate<float> meridiem = {0.8f, 0.0f};

float colourList[8][3] = {
    {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.2f, 0.2f, 1.0f},
    {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f},
    {0.3f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f},
};

float scale = 0.01f;
long unsigned int selectedColourIndex = 0;

inline void cycleColour() {
    selectedColourIndex++;

    if (selectedColourIndex > sizeof(colourList) / sizeof(colourList[0])) {
        selectedColourIndex = 0;
    }
}

inline void drawLeds(bool t_twentyFourHourMode) {
    Coordinate<float>* points = nullptr;
    int size;
    auto drawPoint = [](Coordinate<float>& t_coordinate) {
        glVertex2f(t_coordinate.x, t_coordinate.y);
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &matMaterial[4]);
    glColor3fv(colourList[selectedColourIndex]);
    glPointSize(5.0f);

    if (isStopwatch) {
        points = stopwatchPoints;
        size = sizeof(stopwatchPoints) / sizeof(stopwatchPoints[0]);
    } else {
        points = clockPoints;
        size = sizeof(clockPoints) / sizeof(clockPoints[0]);
    }

    glBegin(GL_POINTS);

    for (int i = 0; i < size; ++i) {
        drawPoint(points[i]);
    }

    if (isStopwatch || t_twentyFourHourMode || !isAfternoon) {
        glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
    }

    drawPoint(meridiem);

    glEnd();
}

inline void drawDigit(int t_digit, int t_i) {
    const int size = sizeof(segments) / sizeof(segments[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &matMaterial[4]);
    glPushMatrix();
    glTranslatef(digitLocations[t_i], 0.0f, 0.0f);

    if (t_digit > 9) {
        t_digit -= 48;
    }

    for (int i = 0; i < size; i++) {
        glPushMatrix();
        glScalef(scale, scale, 0);
        glRotatef(segments[i].rotation, 0.0f, 0.0f, 1.0f);
        glTranslatef(segments[i].x, segments[i].y, 0.0f);
        segmentState[t_digit][i] ? glColor3fv(colourList[selectedColourIndex])
                                 : glColor4f(0.1f, 0.1f, 0.1f, 0.0f);

        glBegin(GL_POLYGON);

        for (auto& segmentPoint : segment) {
            glVertex2f(segmentPoint.x, segmentPoint.y);
        }

        glEnd();
        glPopMatrix();
    }

    glPopMatrix();
}

#endif
