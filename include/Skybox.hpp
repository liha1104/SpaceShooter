#pragma once

#include "SceneObject.hpp"

class Skybox : public SceneObject {
  public:
  Skybox();
  ~Skybox();
  GLuint getSkybox();

  protected:
  virtual void privateInit();
  virtual void privateRender();
  virtual void privateUpdate();

  private:
  std::vector<int> index_array_;
  std::vector<float> vertex_array_;
  GLuint up_;
  GLuint down_;
  GLuint left_;
  GLuint right_;
  GLuint front_;
  GLuint back_;
  GLuint skybox_id_;
  Shader sbShader_;
};
