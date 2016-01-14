#include "materials.h"

#include <GL/glut.h>

const GLfloat defaultMaterial[9] = {
    0.1f,  0.1f, 0.1f, 1.0f,  // ambient & diffuse
    0.8f,  0.8f, 0.8f, 1.0f,  // specular
    128.0f                    // shininess
};

const GLfloat matMaterial[9] = {
    0.1f,  0.1f, 0.1f, 1.0f,  // ambient & diffuse
    0.1f,  0.1f, 0.1f, 1.0f,  // specular
    128.0f                    // shininess
};

void setMaterialProperties(const GLfloat* t_ambient, const GLfloat* t_specular,
                           const GLfloat* t_shininess) {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, t_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, t_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, t_shininess);
};

void setDefaultMaterialProperties() {
    setMaterialProperties(&defaultMaterial[0], &defaultMaterial[4],
                          &defaultMaterial[8]);
};
