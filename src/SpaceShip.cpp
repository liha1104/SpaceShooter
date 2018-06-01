#include "include/SpaceShip.hpp"
#include <iostream>

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::privateInit()
{
  redShader_.loadShaders("shaders/red.vert", "shaders/red.frag");
  matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -80.0f));
}

void SpaceShip::reduceLife()
{
  life_ -= 1;
}

float SpaceShip::getLife()
{
  return life_;
}

void SpaceShip::privateRender()
{

  float diffMat[] = { 1.0f, 0.0f, 0.0f };
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffMat);

  float specMat[] = { 1.0f, 1.0f, 1.0f };
  glMaterialfv(GL_FRONT, GL_SPECULAR, specMat);

  redShader_.enableProgram();

  glutSolidSphere(8, 16, 16);

  redShader_.disableProgram();
}

void SpaceShip::privateUpdate()
{
}

void SpaceShip::moveRight()
{
  if (matrix_[3].x < 110)
    matrix_ = glm::translate(matrix_, glm::vec3(1.5f, 0.0f, 0.0f));
}
void SpaceShip::moveLeft()
{
  if (matrix_[3].x > -110)
    matrix_ = glm::translate(matrix_, glm::vec3(-1.5f, 0.0f, 0.0f));
}
void SpaceShip::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -1.5f, 0.0f));
}
void SpaceShip::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 1.5f, 0.0f));
}
void SpaceShip::moveForward()
{
  if (matrix_[3].z > -200)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -1.5f));
}

void SpaceShip::moveBackward()
{
  if (matrix_[3].z < -45)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 1.5f));
}
