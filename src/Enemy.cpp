
#include "include/Enemy.hpp"
#include <iostream>
#include <math.h>
#include <random>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::privateInit()
{
  std::random_device gen;
  std::mt19937 eng(gen());
  std::uniform_int_distribution<int> dis(0, 2);
  int d = dis(eng);
  if (d == 0)
    t = type_::shooterzz;
  else if (d == 1)
    t = type_::normal;
  else
    t = type_::zigzag;

  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -1000.0f));
}

void Enemy::privateRender()
{
  if (t == type_::shooterzz) {
    //glLoadIdentity();
    glColor3f(1.0f, 0.0f, 1.0f);
  }

  else if (t == type_::normal) {
    //glLoadIdentity();
    glColor3f(1.0f, 1.0f, 0.0f);
  }

  else {
    //glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
  }
  float size = 5.0f;
  glBegin(GL_QUADS);
  // Near Face
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);
  glVertex3f(size, size, size);
  glVertex3f(-size, size, size);
  glEnd();
}

void Enemy::privateUpdate()
{
  if (matrix_[3].x > 115)
    dukdw = 0;
  else if (matrix_[3].x < -115)
    dukdw = 1;

  if (t == type_::normal)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 1.5f));

  else {
    if (dukdw)
      matrix_ = glm::translate(matrix_, glm::vec3(0.3f, 0.0f, 0.7f));
    else
      matrix_ = glm::translate(matrix_, glm::vec3(-0.3f, 0.0f, 0.7f));
  }
}

Enemy::type_ Enemy::getType()
{
  return t;
}
