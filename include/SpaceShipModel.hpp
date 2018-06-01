#pragma once

#include "SceneObject.hpp"

class SpaceShipModel : public SceneObject {
  public:
  SpaceShipModel();
  ~SpaceShipModel();
  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void moveBackward();
  void moveForward();
  void reduceLife();
  float getLife();
  void setLife(float);

  private:
  void privateInit();
  void privateRender();
  void privateUpdate();
  std::vector<glm::vec3> VERT_;
  std::vector<glm::vec3> NORM_;
  std::vector<glm::vec2> TEXC_;
  std::vector<glm::uint> INDI_;
  GLuint texture_;
  float life_ = 3;
  Shader shipShader_;
};
