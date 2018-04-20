#include <iostream>
#include "../include/SpaceShip.hpp"
#include "SOIL.h"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"


SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::privateInit()
{
  matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -80.0f));
}

void SpaceShip::reduceLife()
{
  life_ -= 1;
}

float SpaceShip::getLife()
{
  return life_;
}

void SpaceShip::texturize()
{
  /* load an image file directly as a new OpenGL texture */
  GLuint tex_2d = SOIL_load_OGL_texture
  (
    "../textures/lava.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );

  /* check for an error during the load process */
  if (0 == tex_2d)
  {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }

  // Generate texture name
  glGenTextures(1, &tex_2d);
  // Create texture object
  glBindTexture(GL_TEXTURE_2D, tex_2d);
  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // Set environment mode
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  // Specify texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2400, 1600, 0, GL_RGBA,
    GL_FLOAT, "lava");
  // Enable texturing before render
  glEnable(GL_TEXTURE_2D);
}

void SpaceShip::privateRender()
{
	//glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);
  float size = 5.0f;
  //texturize();
  glBegin(GL_QUADS);
    // Near Face
     //glTexCoord2f(0, 0);
     glVertex3f(-size, -size, size);

     //glTexCoord2f(1, 0);
     glVertex3f( size, -size, size);

     //glTexCoord2f(1, 1);
     glVertex3f( size,  size, size);

     //glTexCoord2f(0, 1);
     glVertex3f(-size,  size, size);
  glEnd();
}

void SpaceShip::privateUpdate()
{

}

void SpaceShip::moveRight()
{
  if(matrix_[3].x < 110)
  matrix_ = glm::translate(matrix_, glm::vec3(1.0f, 0.0f, 0.0f));
}
void SpaceShip::moveLeft()
{
  if (matrix_[3].x > -110)
  matrix_ = glm::translate(matrix_, glm::vec3(-1.0f, 0.0f, 0.0f));
}
void SpaceShip::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -1.0f, 0.0f));
}
void SpaceShip::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 1.0f, 0.0f));
}
void SpaceShip::moveForward()
{
  if (matrix_[3].z > -200)
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -1.0f));
}

void SpaceShip::moveBackward()
{
  if (matrix_[3].z < -45)
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 1.0f));
}

