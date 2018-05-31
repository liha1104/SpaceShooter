#pragma once

#include "SceneObject.hpp"
#include <chrono>

class Enemy : public SceneObject {
  public:
  Enemy();
  ~Enemy();
  enum class type_ { shooterzz,
    normal,
    zigzag };
  type_ getType();
  std::chrono::system_clock::time_point getTime();
  void setTime(std::chrono::_V2::system_clock::time_point);

  protected:
  void privateInit();
  void privateRender();
  void privateUpdate();


  private:
  type_ t;
  bool dukdw = 1;
  float speed_;
  float life_;
  float armor_;
  std::vector<glm::vec3> _VERT;
  std::vector<glm::vec3> _NORM;
  std::vector<glm::vec2> _TEXC;
  std::vector<glm::uint> _INDI;
  Shader shader_;
  std::chrono::_V2::system_clock::time_point endwait3 = std::chrono::system_clock::now();
};
