#include "GL_Triangle.hpp"

void GL_Triangle::draw()
{
    glColor3d(0, 1, 0);
    glBegin(GL_TRIANGLES);
    glVertex2d(0, 0);
    glVertex2d(400, 0);
    glVertex2d(400, 300);
    glRotatef(30, 0, 0, 0);
    glEnd();
}
