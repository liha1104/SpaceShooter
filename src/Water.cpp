#include "include/Water.hpp"
#include <iostream>

Water::Water()
{
}

Water::~Water()
{
}

void Water::privateInit()
{
  wShader_.loadShaders("shaders/water.vert", "shaders/water.frag");

  texture_ = SOIL_load_OGL_cubemap
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

  const float spacing = 10;
   const float offset = -320;
   const float y = -10;

   const int vWidth = 64;
   const int vDepth = 128;

   // Create vertex arrays
   for(int i = 0; i < vDepth; ++i)
   {
     for(int j = 0; j < vWidth; ++j)
     {
       auto x = offset + j*spacing;
       auto z = i*spacing;
       vertexArray_.push_back(glm::vec3(x, y, -z + 100));
       texArray_.push_back(glm::vec2(j/float(vWidth-1), i/float(vDepth-1)));//31, 511
       //          vertexArray_.push_back(glm::vec3(x + spacing, y, -z));
       //          vertexArray_.push_back(glm::vec3(x + spacing, y, -(z + spacing)));
       //          vertexArray_.push_back(glm::vec3(x, y, -(z + spacing)));
     }
   }
   for(glm::uint i = 1; i < vDepth; ++i)
   {
     for(glm::uint j = 0; j < vWidth; ++j)
     {
       auto top = vWidth * i + j;
       auto bottom = vWidth * (i-1) + j;

       indiceArray_.push_back(top);
       indiceArray_.push_back(bottom);
       //                      glm::vec2(top, bottom));
     }
     indiceArray_.push_back(UINT_MAX);
   }
}

void Water::privateRender()
{
  wShader_.enableProgram();

    //glActiveTexture(texture_);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);

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

    GLint bsLocation = glGetUniformLocation(wShader_.getProgram(), "rand");
    glUniform1f(bsLocation, waterVar += 1);

    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(UINT_MAX);
    glDrawElements(GL_TRIANGLE_STRIP, indiceArray_.size(), GL_UNSIGNED_INT, &indiceArray_[0]);

    glDisable(GL_PRIMITIVE_RESTART);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_CUBE_MAP);

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);

    glDisable(GL_BLEND);

    wShader_.disableProgram();
}

void Water::privateUpdate()
{

}

