#include "include/Skybox.hpp"
#include <limits.h>

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}

void Skybox::privateInit()
{

  sbShader_.loadShaders("shaders/skybox.vert", "shaders/skybox.frag");


  _skybox_id = SOIL_load_OGL_cubemap
    ( (_sboxpath + "right.jpg").c_str(),
      (_sboxpath + "left.jpg").c_str(),
      (_sboxpath + "up.jpg").c_str(),
      (_sboxpath + "down.jpg").c_str(),
      (_sboxpath + "back.jpg").c_str(),
      (_sboxpath + "front.jpg").c_str(),
      SOIL_LOAD_RGB,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS
    );

  float size = 1.0f / 2.0f;

    _vertex_array = {
      -size, -size, -size, -size,
      size, -size, size, size,
      -size, size, -size, -size,
      size, -size, size, size,
      size, size, -size, -size,
      size, -size, size, size,
    };

    _index_array = {
      0, 2, 1,
      2, 0, 3,
      2, 3, 4,
      5, 2, 4,
      4, 6, 5,
      5, 6, 7,
      0, 7, 6,
      1, 7, 0,
      0, 6, 3,
      6, 4, 3,
      1, 2, 7,
      7, 2, 5,
    };

}

void Skybox::privateRender()
{

  sbShader_.enableProgram();
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.0f, 0.0f, 0.0f);

    //glActiveTexture(_skybox_id); // gives error: invalid enumerant in console
    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skybox_id);

    // Draw Cube
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &_vertex_array[0]);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glDrawElements(GL_TRIANGLES, static_cast<int>(_index_array.size()), GL_UNSIGNED_INT, &_index_array[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_CUBE_MAP);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);

    glEnable(GL_DEPTH_TEST);

    sbShader_.disableProgram();


}

void Skybox::privateUpdate()
{
}

GLuint Skybox::getSkybox()
{
  return _skybox_id;
}
