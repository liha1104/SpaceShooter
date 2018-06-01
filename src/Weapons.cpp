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
  return o_;
}

Weapons::type_ Weapons::getType()
{
  return t_;
}

void Weapons::privateInit()
{
}

void Weapons::privateRender()
{
  if (getType() == type_::bullet && getOwner() == owner_::ship) {
    glColor3f(1.0f, 1.0f, 0.0f);
    float size = 1.0f;
    glBegin(GL_QUADS);
    // Near Face
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();
  }
  else if (getType() == type_::rocket && getOwner() == owner_::ship) {

    glColor3f(1.0f, 0.8f, 0.0f);
    float size = 2.5f;
    glBegin(GL_QUADS);
    // Near Face
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    glEnd();
  }

  if (getOwner() == owner_::enemy) {
    glColor3f(0.0f, 0.8f, 0.8f);
    float size = 2.0f;
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
  if (o_ == owner_::enemy)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 12.0f));
  else if (getType() == type_::bullet)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -17.0f));
  else if (getType() == type_::rocket)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -12.0f));
}

void Weapons::setOwner(owner_ ob)
{
  o_ = ob;
}

void Weapons::setType(type_ ty)
{
  t_ = ty;
}
