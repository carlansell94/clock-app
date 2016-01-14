#ifndef MATERIALS_H
#define MATERIALS_H

#include <GL/glut.h>

extern const GLfloat defaultMaterial[9];

extern const GLfloat matMaterial[9];

void setMaterialProperties(const GLfloat* t_ambient, const GLfloat* t_specular,
                           const GLfloat* t_shininess);

void setDefaultMaterialProperties();

#endif
