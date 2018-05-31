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
  std::vector<int> _index_array;
  std::vector<float> _vertex_array;
  GLuint up;
  GLuint down;
  GLuint left;
  GLuint right;
  GLuint front;
  GLuint back;
  GLuint _skybox_id;
  Shader sbShader_;

};
