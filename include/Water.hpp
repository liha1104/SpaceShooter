#include "SceneObject.hpp"

//Pure waah, fefty pence, teystes like fak all
class Water : public SceneObject {
  public:
  Water();
  ~Water();

  protected:
  virtual void privateInit();
  virtual void privateRender();
  virtual void privateUpdate();

  private:
  std::vector<glm::vec3> vertexArray_;
  std::vector<glm::uint> indiceArray_;
  std::vector<glm::vec2> texArray_;

  GLuint texture_;
  Shader wShader_;

  float waterVar = 0;
};
