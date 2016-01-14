#ifndef SCENE_H
#define SCENE_H

#include "coordinate.h"
#include "materials.h"

const float defaultCameraX = 0.0f;
const float defaultCameraY = 1.0f;
const float defaultCameraZ = 4.0f;

Coordinate<float> cameraPosition = {defaultCameraX, defaultCameraY,
                                    defaultCameraZ};

const GLfloat defaultLighting[16] = {
    2.0f,  0.5f,  3.0f,  1.0f,  // position
    0.2f,  0.2f,  0.2f,  1.0f,  // ambient
    0.25f, 0.25f, 0.25f, 1.0f,  // diffuse
    1.0f,  1.0f,  1.0f,  1.0f   // emission
};

inline void setSceneLighting() {
    glLightfv(GL_LIGHT0, GL_POSITION, &defaultLighting[0]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, &defaultLighting[4]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &defaultLighting[8]);
    glLightfv(GL_LIGHT0, GL_EMISSION, &defaultLighting[12]);
    glEnable(GL_LIGHT0);
}

inline void setViewport(const int &t_width, const int &t_height) {
    const float ratio = static_cast<float>(t_width) / t_height;
    glOrtho(0, t_width, 0, t_height, -1, 1);
    glViewport(0, 0, t_width, t_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, ratio, 1.0, 10.0);
}

inline void cameraInit() {
    setSceneLighting();
    setDefaultMaterialProperties();
    setViewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, 0, 0, 0, 0,
              1, 0);
}

// Camera controls
inline void cameraZoomIn() {
    if (cameraPosition.z > 2.0f) cameraPosition.z -= 0.25f;
}

inline void cameraZoomOut() {
    if (cameraPosition.z < 7.5f) cameraPosition.z += 0.25f;
}

inline void cameraMoveLeft() {
    if (cameraPosition.x > -4.0f) cameraPosition.x -= 0.25f;
}

inline void cameraMoveRight() {
    if (cameraPosition.x < 4.0f) cameraPosition.x += 0.25f;
}

inline void cameraMoveUp() {
    if (cameraPosition.y < 4.0f) cameraPosition.y += 0.25f;
}

inline void cameraMoveDown() {
    if (cameraPosition.y > -4.0f) cameraPosition.y -= 0.25f;
}

inline void cameraReset() {
    cameraPosition.x = defaultCameraX;
    cameraPosition.y = defaultCameraY;
    cameraPosition.z = defaultCameraZ;
}

#endif
