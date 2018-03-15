#include <math.h>
#include "../include/Weapons.hpp"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"


Weapons::Weapons()
{
}

Weapons::~Weapons()
{
}

void Weapons::privateInit()
{
}

void Weapons::privateRender()
{
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

void Weapons::privateUpdate()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -2.0f));
}