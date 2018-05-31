 #pragma once


#include "SceneObject.hpp"


class Water : public SceneObject
{
  public:
    Water();
    ~Water();

  protected:
    void privateInit();
    void privateRender();
    void privateUpdate();
    bool markedForDeletion();

  private:
    std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
    std::vector< glm::uint > indicesArray_;
    std::vector< glm::vec2 > _texCoordArray;
    std::vector< GLint > _waterData;
    // normal array.
    // texture coord array
    GLuint _texture;
    GLint _texColormapSampler;
    GLint _waterDataSampler;

    Shader waterShader;
    float amount = 0;
};
