
#include <math.h>
#include "../include/Enemy.hpp"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::privateInit()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -1000.0f));
}

void Enemy::privateRender()
{
  //glLoadIdentity();
  glColor3f(0.0f, 0.0f, 1.0f);
  float size = 5.0f;
  glBegin(GL_QUADS);
  // Near Face
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);
  glVertex3f(size, size, size);
  glVertex3f(-size, size, size);
  glEnd();

}



// double x = 0.1f;
void Enemy::privateUpdate()
{

  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 0.3f));
  /*auto a = 4.0 * sin(0.1* M_PI *x);
  matrix_ = glm::translate(matrix_, glm::vec3(a , 0.0, 0.1));
  x = a;*/
  matrix_ = glm::rotate(matrix_, (glm::mediump_float)0.01, glm::vec3(0.0f, 0.0f, 0.6f));
}

