#pragma once

#include "SceneObject.hpp"


class SpaceShip : public SceneObject {
  public:
  SpaceShip();
  ~SpaceShip();
  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void moveBackward();
  void moveForward();
  void reduceLife();
  float getLife();

  protected:
  void privateInit();
  void privateRender();
  void privateUpdate();
  void texturize();

  private:
  float speed_;
  float life_ = 3;
  float armor_;
  Shader redShader_;
};
