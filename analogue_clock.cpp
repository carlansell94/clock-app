#include "analogue_clock.h"

#include <array>
#include <cmath>
#include <vector>

#include "button.h"
#include "characters.h"
#include "coordinate.h"
#include "hands.h"
#include "time.h"

unsigned int selectedImage = 0;
unsigned int lastSelectedImage = 0;
GLuint texture = 0;

float* AnalogueClock::getButtonPositions() {
    static float buttonPositions[10] = {-0.42f, -0.14f, -0.14f, 0.14f, 0.14f,
                                        0.42f,  0.34f,  0.45f,  1.0f,  -1.0f};
    return buttonPositions;
}

const std::vector<Button> AnalogueClock::buttonList = {
    {-0.25f, "reset", -0.04f},
    {0.0f, "mode", -0.04f},
    {0.25f, "start", -0.07f}};

const Coordinate<float> AnalogueClock::buttonVertices[] = {
    {-0.42f, 0.35f, 0.001f},
    {0.42f, 0.35f, 0.001f},
    {0.42f, 0.45f, 0.001f},
    {-0.42f, 0.45f, 0.001f}};

// List of texture paths along with a boolean to define whether clock markers
// should be added
const std::array<ClockFaceTexture, 4> AnalogueClock::textures = {
    ClockFaceTexture{"images/wood.png", true},
    ClockFaceTexture{"images/cloud.png", true},
    ClockFaceTexture{"images/splodgey.png", true},
    ClockFaceTexture{"images/square.png", false}};

void AnalogueClock::loadTexture() {
    texture = bindTexture(textures[selectedImage - 1].filePath);
}

void AnalogueClock::cycleTexture() {
    constexpr int textureCount = textures.size();

    if (selectedImage == textureCount) {
        selectedImage = 0;
    } else {
        selectedImage++;
    }
}

void AnalogueClock::changeHandWidth() {
    const float maxHandWidth = 9.0f;
    const float minHandWidth = 2.0f;
    handWidth += 1.0f;

    if (handWidth > maxHandWidth) {
        handWidth = minHandWidth;
    }
}

void AnalogueClock::drawButton(const Button& t_button) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(1.1f);
    glTranslatef(t_button.position + t_button.labelOffset, 0.4f, 0.001f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertexPointer(2, GL_FLOAT, 0, letterPoints);
    drawString(t_button.label);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void AnalogueClock::drawButtons() {
    for (const Button& button : buttonList) {
        glPushMatrix();
        drawButton(button);
        glPopMatrix();
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);

    for (const Coordinate<float>& vertex : buttonVertices) {
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }

    glEnd();
}

void AnalogueClock::drawClockFaceMarkers() {
    const float translate = 0.84f;
    const float length = 0.1f;
    float theta = 0.0f;

    constexpr float segments = 60;
    constexpr float angle = 360 / segments;

    glColor3f(0.0f, 0.0f, 0.0f);

    for (size_t i = 0; i < segments; i++, theta += angle) {
        glPushMatrix();
        glRotatef(theta, 0.0f, 0.0f, 1.0f);

        if (i % 5 == 0) {
            glTranslatef(0.0f, translate - 0.05f, 0.0f);
        } else {
            glTranslatef(0.0f, translate, 0.0f);
            glScalef(1.0f, 0.5f, 1.0f);
        }

        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.01f);
        glVertex3f(0.0f, length, 0.01f);
        glEnd();
        glPopMatrix();
    }
}

void AnalogueClock::drawClockFace() {
    float lastx = 0.0f;
    float lasty = 0.0f;
    const float pi = atan(1) * 4;
    const size_t steps = 60;
    const float theta_step = 2 * pi / float(steps - 1);
    float theta = 0.0f;

    for (size_t i = 0; i < steps; i++, theta += theta_step) {
        float x = clockFaceRadius * cosf(theta);
        float y = clockFaceRadius * sinf(theta);

        glBegin(GL_POLYGON);
        glVertex2f(lastx, lasty);
        glVertex2f(x, y);
        glVertex2f(0.0f, 0.0f);
        glEnd();

        lastx = x;
        lasty = y;
    }

    drawClockFaceMarkers();
}

void AnalogueClock::drawTexturedClockFace() {
    // Map out edges of shape
    const float vertex[4][2] = {{clockFaceRadius, clockFaceRadius},
                                {clockFaceRadius, -clockFaceRadius},
                                {-clockFaceRadius, -clockFaceRadius},
                                {-clockFaceRadius, clockFaceRadius}};

    const float textureEdges[4][2] = {
        {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f}};

    if (selectedImage != lastSelectedImage) {
        loadTexture();
        lastSelectedImage = selectedImage;
    }

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, selectedImage);

    glBegin(GL_QUADS);
    for (size_t i = 0; i < 4; i++) {
        glTexCoord2fv(textureEdges[i]);
        glVertex2fv(vertex[i]);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void AnalogueClock::reset() {
    handStyle = 0;
    selectedImage = 0;
    lastSelectedImage = 0;
    texture = 0;
    handWidth = 3.0f;
}

void AnalogueClock::checkKeyPress(unsigned char key) {
    switch (key) {
        case 'f':
            cycleTexture();
            break;
        case 'h':
            cycleHandStyle();
            break;
        case 'w':
            changeHandWidth();
            break;
    }
}

void AnalogueClock::display(bool t_showDate = false) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(handWidth);

    if (selectedImage == 0) {
        drawClockFace();
    } else {
        drawTexturedClockFace();

        if (textures[selectedImage - 1].showClockFaceMarkers) {
            drawClockFaceMarkers();
        }
    }

    if (isStopwatch) {
        drawStopWatchHands();
    } else {
        drawClockHands();
    }

    if (t_showDate) {
        drawDate(0.0f, 0.0f, 0.0f);
    }

    drawButtons();
}
