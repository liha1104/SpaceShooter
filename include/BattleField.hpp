#pragma once

#include "SceneObject.hpp"


class BattleField : public SceneObject {
  public:
  BattleField();
  ~BattleField();

  protected:
  virtual void privateInit();
  virtual void privateRender();
  virtual void privateUpdate();
  void loadTex(GLuint);

  private:
  std::vector<glm::vec3> vertexArray_; // Maybe two-dim vector and several arrays
  std::vector<glm::uint> indexArray_;
  std::vector<glm::vec2> texArray_;
  GLuint tex_hm;
  GLuint tex_cm;
  Shader mShader_;

  glm::uint _RESET = 1000000000;
  // normal array.
  // texture coord array
};
