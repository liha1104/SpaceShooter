#include "../include/BattleField.hpp"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"


BattleField::BattleField()
{
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
  // Create vertex arrays
  auto const X_LENGTH = 10, Z_LENGTH = 10, y = -10;
  for (auto i = 0; i < 512; ++i) {
    for (auto j = 0; j < 32; ++j) {
      auto x = j*X_LENGTH, z = i*Z_LENGTH;
      vertexArray_.push_back(glm::vec3{ x, y, -z });
      texArray_.push_back(glm::vec2{x/512.0f, -(z+32)/32.0f});
    }
  }
  for (glm::uint i = 1; i < 512; ++i) {
    for (glm::uint j = 0; j < 32; ++j) {
      auto top = 32 * i + j;
      auto bot = 32 * (i - 1) + j;;
      indexArray_.push_back(top);
      indexArray_.push_back(bot);
    }
    indexArray_.push_back(UINT_MAX);
  }
  loadTex();
}

void BattleField::privateRender()
{
  // activate and specify pointer to vertex array
  glColor3d(1.0, 1.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex_2d);
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
  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_VERTEX_ARRAY);

}

void BattleField::privateUpdate()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 1.0f));
}

void BattleField::loadTex()
{
  /* load an image file directly as a new OpenGL texture */
  tex_2d = SOIL_load_OGL_texture
  (
    "C:\\Users\\Victor\\Documents\\VS17 Projects\\AlienElimination\\AlienElimination\\textures\\lava.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );

  if (0 == tex_2d)
  {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }

}

