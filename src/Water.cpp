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
  waterShader.loadShaders("shaders/water.vert", "shaders/water.frag");

  _texture = SOIL_load_OGL_texture
  (
    "textures/water.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  /* check for an error during the load process */
  if (0 == _texture)
  {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }

  const int
    BLOCK_SIZE = 30,
    BLOCK_DIVIDED = BLOCK_SIZE / 2,
    BLOCK_LENGTH = 30,
    SCALAR_X = 1,
    SCALAR_Y = 1,
    SCALAR_Z = 1;

  const float
    START_X = BLOCK_DIVIDED,
    START_Y = -5,
    START_Z = 5;

  for (int i = 0; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_LENGTH; ++j) {
      vertexArray_.push_back(glm::vec3{ (-i + START_X) * SCALAR_X, (START_Y)* SCALAR_Y , (-j + START_Z) * SCALAR_Z });
      _texCoordArray.push_back(glm::vec2{ float(i) / float(BLOCK_SIZE), float(j) / float(BLOCK_LENGTH) });
    }
  }

  for (int i = 1; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_LENGTH; ++j) {
      indicesArray_.push_back(j + (BLOCK_LENGTH * i));
      indicesArray_.push_back(j + (BLOCK_LENGTH * (i - 1)));
    }
    indicesArray_.push_back(UINT_MAX);
  }

  // Make water data
  /*
  for (int i = 1; i < BLOCK_SIZE; ++i) {
    for (int j = 0; j < BLOCK_LENGTH; ++j) {
      _waterData.push_back(GLint(i));
    }
  }
  */

  waterShader.enableProgram();
  _texColormapSampler = glGetUniformLocation(waterShader.getProgram(), "tex_colormap");
  _waterDataSampler = glGetUniformLocation(waterShader.getProgram(), "water_data");
  glUniform1i(_texColormapSampler, 0); // Set ”tex_colormap” to use GL_TEXTURE0
  glUniform1i(_waterDataSampler, amount);
  waterShader.disableProgram();
}

void Water::privateRender()
{
  waterShader.enableProgram();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glUniform1f(_waterDataSampler, amount);

  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_PRIMITIVE_RESTART);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glPrimitiveRestartIndex(UINT_MAX);
  glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
  glTexCoordPointer(2, GL_FLOAT, 0, &_texCoordArray[0]);

  glDrawElements(GL_TRIANGLE_STRIP,
    indicesArray_.size(),
    GL_UNSIGNED_INT,
    &indicesArray_[0]);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glDisable(GL_PRIMITIVE_RESTART);

  glActiveTexture(GL_TEXTURE0);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);

  waterShader.disableProgram();
}

void Water::privateUpdate()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 7.0f));
  amount += 0.005;
  if (amount >= 360)
  {
    amount = 0;
  }
  //std::cout << amount << std::endl;
}

