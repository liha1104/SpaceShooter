#include "include/Weapons.hpp"
#include <math.h>

Weapons::Weapons()
{
}

Weapons::~Weapons()
{
}

Weapons::owner_ Weapons::getOwner()
{
  return o;
}

Weapons::type_ Weapons::getType()
{
  return t;
}

void Weapons::privateInit()
{
}

void Weapons::privateRender()
{
  if (getType() == type_::bullet || getOwner() == owner_::enemy) {
    //glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    float size = 1.0f;
    glBegin(GL_QUADS);
    // Near Face
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();
  }
  else if (getType() == type_::rocket) {
    //glLoadIdentity();
    glColor3f(0.5f, 0.1f, 0.5f);
    float size = 3.0f;
    glBegin(GL_QUADS);
    // Near Face
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();
  }
}

void Weapons::privateUpdate()
{
  if (o == owner_::enemy)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
  else if (getType() == type_::bullet)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -5.0f));
  else if (getType() == type_::rocket)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}

void Weapons::setOwner(owner_ ob)
{
  o = ob;
}

void Weapons::setType(type_ ty)
{
  t = ty;
}
