#include "include/Camera.hpp"

#define PIOVER180 0.0174532925199

Camera::Camera()
{
  matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, -35.0f, -40.0f));
  //matrix_ = glm::rotate(matrix_, (glm::mediump_float)0.5, glm::vec3(1.0f, 0.0f, 0.0f));
}

Camera::~Camera()
{
}

void Camera::privateInit()
{
}

void Camera::privateRender()
{
  // not drawing any camera geometry
}

void Camera::privateUpdate()
{
}

void Camera::moveRight()
{
  matrix_ = glm::translate(matrix_, glm::vec3(-3.0f, 0.0f, 0.0f));
}
void Camera::moveLeft()
{
  matrix_ = glm::translate(matrix_, glm::vec3(3.0f, 0.0f, 0.0f));
}
void Camera::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -3.0f, 0.0f));
}
void Camera::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 3.0f, 0.0f));
}
void Camera::moveForward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 3.0f));
}
void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -3.0f));
}
