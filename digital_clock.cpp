#include "digital_clock.h"

#include <GL/glut.h>
#include <stdbool.h>

#include <string>

#include "button.h"
#include "characters.h"
#include "digit.h"
#include "materials.h"
#include "time.h"

bool twentyFourHourMode = true;

float* DigitalClock::getButtonPositions() {
    static float buttonPositions[10] = {-0.6f, -0.4f, -0.1f, 0.1f,   0.4f,
                                        0.6f,  0.4f,  0.45,  -0.14f, -0.34f};
    return buttonPositions;
}

const std::vector<Button> DigitalClock::buttonList = {
    {-0.5f, "reset", -0.04f}, {0.0f, "mode", -0.04f}, {0.5f, "start", -0.07f}};

const Coordinate<float> DigitalClock::frameVertices[28] = {
    // Define vertices for clock frame
    {-0.9f, 0.4f, 0.0f},   {-0.9f, -0.4f, 0.0f},  {0.9f, -0.4f, 0.0f},
    {0.9f, 0.4f, 0.0f},    {-0.8f, 0.3f, -0.01f}, {-0.8f, -0.3f, -0.01f},
    {0.7f, -0.3f, -0.01f}, {0.7f, 0.3f, -0.01f},  {-0.9f, 0.4f, 0.0f},
    {0.9f, 0.4f, 0.0f},    {0.9f, 0.4f, -0.5f},   {-0.9f, 0.4f, -0.5f},
    {-0.9f, 0.4f, -0.5f},  {0.9f, 0.4f, -0.5f},   {0.9f, -0.4f, -0.5f},
    {-0.9f, -0.4f, -0.5f}, {-0.9f, -0.4f, -0.5f}, {0.9f, -0.4f, -0.5f},
    {0.9f, -0.4f, 0.0f},   {-0.9f, -0.4f, 0.0f},  {-0.9f, -0.4f, 0.0f},
    {-0.9f, 0.4f, 0.0f},   {-0.9f, 0.4f, -0.5f},  {-0.9f, -0.4f, -0.5f},
    {0.9f, -0.4f, 0.0f},   {0.9f, 0.4f, 0.0f},    {0.9f, 0.4f, -0.5f},
    {0.9f, -0.4f, -0.5f},
};

const float DigitalClock::frameNormals[28][3] = {
    // Define normals for clock frame
    {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},  {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
};

const GLubyte DigitalClock::frame[] = {
    // Define faces for clock frame
    0,  4,  5,  0,  1,  5,  1,  5,  2,  5,  2,  6,  2,  3,  6,  6,  7,  3,
    7,  3,  4,  3,  0,  4,  8,  9,  10, 8,  10, 11, 12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23, 24, 25, 26, 24, 26, 27,
};

const Coordinate<float> DigitalClock::buttonVertices[20] = {
    // Define vertices for buttons
    {-0.1f, 0.45f, -0.15f}, {0.1f, 0.45f, -0.15f},  {0.1f, 0.4f, -0.15f},
    {-0.1f, 0.4f, -0.15f},  {-0.1f, 0.45f, -0.15f}, {0.1f, 0.45f, -0.15f},
    {0.1f, 0.45f, -0.35f},  {-0.1f, 0.45f, -0.35f}, {-0.1f, 0.45f, -0.35f},
    {0.1f, 0.45f, -0.35f},  {0.1f, 0.4f, -0.35f},   {-0.1f, 0.4f, -0.35f},
    {-0.1f, 0.4f, -0.15f},  {-0.1f, 0.45f, -0.15f}, {-0.1f, 0.45f, -0.35f},
    {-0.1f, 0.4f, -0.35f},  {0.1f, 0.45f, -0.15f},  {0.1f, 0.4f, -0.15f},
    {0.1f, 0.4f, -0.35f},   {0.1f, 0.45f, -0.35f},
};

const float DigitalClock::buttonNormals[20][3] = {
    // Define normals for buttons
    {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},  {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f, 0.0f},  {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, -1.0f},
    {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f, 0.0f},
};

const GLubyte DigitalClock::button[] = {
    // Define faces for buttons
    0, 1,  3,  1,  2,  3,  4,  5,  6,  4,  6,  7,  8,  9,  10,
    8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19,
};

const GLubyte DigitalClock::surround[] = {
    4, 5, 6, 7};  // Define faces for digit surround

void DigitalClock::toggleHourMode() {
    twentyFourHourMode = !twentyFourHourMode;
}

void DigitalClock::buttonText() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertexPointer(2, GL_FLOAT, 0, letterPoints);

    glPushMatrix();
    glTranslatef(0.78f, -0.05f, 0.01f);
    drawString("pm");
    glPopMatrix();
}

void DigitalClock::drawButton(const Button& t_button) {
    // button frame
    glTranslatef(t_button.position, 0.0f, 0.0f);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColor3f(0.3f, 0.3f, 0.3f);
    glNormalPointer(GL_FLOAT, 0, buttonNormals);
    glVertexPointer(3, GL_FLOAT, 0, buttonVertices);
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_BYTE, button);
    glDisableClientState(GL_NORMAL_ARRAY);

    // button label
    glTranslatef(t_button.labelOffset, 0.35f, 0.01f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertexPointer(2, GL_FLOAT, 0, letterPoints);
    drawString(t_button.label);
}

void DigitalClock::drawButtons() {
    for (const Button& button : buttonList) {
        glPushMatrix();
        drawButton(button);
        glPopMatrix();
    }
}

void DigitalClock::drawDigitalClockFrame() {
    glEnableClientState(GL_NORMAL_ARRAY);
    glColor3f(0.2f, 0.2f, 0.2f);
    glNormalPointer(GL_FLOAT, 0, frameNormals);
    glVertexPointer(3, GL_FLOAT, 0, frameVertices);
    glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_BYTE, frame);
    glDisableClientState(GL_NORMAL_ARRAY);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &matMaterial[4]);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertexPointer(3, GL_FLOAT, 0, frameVertices);           // Load vertices
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, surround);  // Draw surround
    setDefaultMaterialProperties();
}

void DigitalClock::drawDigitalClock() {
    glLineWidth(1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    drawDigitalClockFrame();
    buttonText();
    drawLeds(twentyFourHourMode);
    drawButtons();

    glDisableClientState(GL_VERTEX_ARRAY);
}

void DigitalClock::reset() {
    scale = 0.01f;
    selectedColourIndex = 0;
    twentyFourHourMode = false;
}

void DigitalClock::checkKeyPress(unsigned char key) {
    switch (key) {
        case 'c':
            cycleColour();
            break;
        case 'h':
            toggleHourMode();
            break;
    }
}

void DigitalClock::display(bool t_showDate = false) {
    std::string displayTime;
    drawDigitalClock();

    if (isStopwatch) {
        displayTime = getStopwatchTimeString();
    } else {
        displayTime = getCurrentTimeString(twentyFourHourMode);
    }

    for (int i = 0; i < 6; i++) {
        drawDigit(displayTime[i], i);
    }

    if (t_showDate) {
        drawDate(1.0f, 1.0f, 1.0f);
    }
}
