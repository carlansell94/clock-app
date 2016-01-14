#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include <GL/glut.h>
#include <stddef.h>
#include <string.h>

inline void drawText(const int x_pos, const int y_pos, const char* text) {
    const float scale = 0.1f;

    glLineWidth(1.0f);
    glPointSize(1.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x_pos, y_pos, 0.0f);
    glScalef(scale, scale, 1.0f);
    size_t len = strlen(text);
    for (size_t i = 0; i < len; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

#endif
