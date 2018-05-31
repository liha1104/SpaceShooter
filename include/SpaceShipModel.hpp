#pragma once

#include "SceneObject.hpp"


class SpaceShipModel : public SceneObject
{
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



private:
  void privateInit();
  void privateRender();
  void privateUpdate();

//	GLuint _texture;
//	GLint _texColormapSampler;

  /*
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normal;
  std::vector<glm::vec2> texCoords;
  std::vector<glm::uint> indices;
  */
  std::vector<glm::vec3> _VERT;
  std::vector<glm::vec3> _NORM;
  std::vector<glm::vec2> _TEXC;
  std::vector<glm::uint> _INDI;
  GLuint _texture;
  float life_ = 3;
  Shader shipShader_;

};
