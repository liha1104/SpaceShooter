#include "include/BattleField.hpp"
#include <limits.h>

BattleField::BattleField()
{
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{

  mShader_.loadShaders("shaders/map.vert", "shaders/map.frag");

  /* load an image file directly as a new OpenGL texture */
  tex_cm_ = SOIL_load_OGL_texture(
      (_texturepath + "colorm.bmp").c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

  if (0 == tex_cm_) {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }

  /* load an image file directly as a new OpenGL texture */
  tex_hm_ = SOIL_load_OGL_texture(
      (_texturepath + "heightm.bmp").c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

  if (0 == tex_hm_) {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }


  mShader_.enableProgram();

    GLuint _shader_height_map = glGetUniformLocation(mShader_.getProgram(), "height");
    GLuint _shader_colour_map = glGetUniformLocation(mShader_.getProgram(), "color");
    glUniform1i(_shader_height_map, 0);
    glUniform1i(_shader_colour_map, 1);

//  mShader_.enableProgram();
//  GLint texSampler0;
//  GLint texSampler1;
//  texSampler0 = glGetUniformLocation(tex_hm, "height");
//  glUniform1i(texSampler0, 0);
//  texSampler1 = glGetUniformLocation(tex_cm, "color");
//  glUniform1i(texSampler1, 1);
  mShader_.disableProgram();

  // Create vertex arrays
  auto const X_LENGTH = 10, Z_LENGTH = 10, y = -10;
  for (auto i = 0; i < 512; ++i) {
    for (auto j = 0; j < 64; ++j) {
      auto x = j * X_LENGTH, z = i * Z_LENGTH;
      vertexArray_.push_back(glm::vec3{ x, y, -z });
      texArray_.push_back(glm::vec2{ i / 511.0f, j / 63.0f });
    }
  }
  for (glm::uint i = 1; i < 512; ++i) {
    for (glm::uint j = 0; j < 64; ++j) {
      auto top = 64 * i + j;
      auto bot = 64 * (i - 1) + j;
      indexArray_.push_back(top);
      indexArray_.push_back(bot);
    }
    indexArray_.push_back(UINT_MAX);
  }
  //loadTex();
}

void BattleField::privateRender()
{

//        GLuint color = glGetUniformLocation(map.getProg(), "color");
//        GLuint height = glGetUniformLocation(map.getProg(), "height");
//        map.enable();
//        glUniform1i(color, 0);
//        glUniform1i(height, 1);
//        glActiveTexture(GL_TEXTURE0 + 0);
//        glBindTexture(GL_TEXTURE_2D, colorMap);
//        glActiveTexture(GL_TEXTURE0 + 1);
//        glBindTexture(GL_TEXTURE_2D, heightMap);


  // activate and specify pointer to vertex array
  mShader_.enableProgram();
  //glColor3d(1.0, 1.0, 1.0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex_hm_);
  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, tex_cm_);
  glEnable(GL_TEXTURE_2D);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(UINT_MAX);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
  glTexCoordPointer(2, GL_FLOAT, 0, &texArray_[0]);
  // draw a cube
  //glDrawElements(GL_TRIANGLE_STRIP, indexArray_.size(), GL_UNSIGNED_BYTE, &indexArray_);
  glDrawElements(GL_TRIANGLE_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);
  // deactivate vertex arrays after drawing
  glDisable(GL_PRIMITIVE_RESTART);
  glActiveTexture(GL_TEXTURE1);
  glDisable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  mShader_.disableProgram();
}

void BattleField::privateUpdate()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 10.0f));
}

void BattleField::loadTex(GLuint t)
{
  /* load an image file directly as a new OpenGL texture */
  t = SOIL_load_OGL_texture(
      (_texturepath + "heightm.bmp").c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

  if (0 == t) {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }
}
