#include "include/Particles.hpp"

void Particles::prepareRender()
{
  particleEffect_.enableProgram();
  GLuint color = glGetUniformLocation(particleEffect_.getProgram(), "color");
  glUniform1i(color, 0);
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glActiveTexture(GL_TEXTURE0 + 0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, partTex_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  fadeEffect_ = glGetUniformLocation(particleEffect_.getProgram(), "fade");
}

void Particles::disableRender()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  particleEffect_.disableProgram();
}

Particles::Particles(glm::mat4& m)
{
  this->privateInit();
}

void Particles::privateUpdate() {}
void Particles::privateInit()
{
  particleEffect_.loadShaders("shaders/part.vert", "shaders/part.frag");
  /* load an image file directly as a new OpenGL texture */
  partTex_ = SOIL_load_OGL_texture(
      (_texturepath + "particle.bmp").c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

  if (0 == partTex_) {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }

  for (loop_ = 0; loop_ < MAX_PARTICLES; loop_++) {
    particle[loop_].active = true;
    particle[loop_].life = 1.0f;
    particle[loop_].fade = float(rand() % 100) / 1000.0f + 0.003f;
    particle[loop_].r = colors[loop_ * (12 / MAX_PARTICLES)][0];
    particle[loop_].g = colors[loop_ * (12 / MAX_PARTICLES)][1];
    particle[loop_].b = colors[loop_ * (12 / MAX_PARTICLES)][2];
    particle[loop_].xi = float((rand() % 50) - 26.0f) * 100.0f;
    particle[loop_].yi = float((rand() % 50) - 25.0f) * 100.0f;
    particle[loop_].zi = float((rand() % 50) - 25.0f) * 100.0f;
    particle[loop_].xg = 0.0f;
    particle[loop_].yg = -0.8f;
    particle[loop_].zg = 0.0f;
    particle[loop_].x = matrix_[3].x;
    particle[loop_].y = matrix_[3].y;
    particle[loop_].z = matrix_[3].z;
  }
}

void Particles::privateRender()
{
  bool faded = false;
  prepareRender();

  for (loop_ = 0; loop_ < MAX_PARTICLES; loop_++) {
    if (particle[loop_].active) {
      float x = particle[loop_].x;
      float y = particle[loop_].y;
      float z = particle[loop_].z;

      glBegin(GL_QUADS);
      glTexCoord2d(1, 1);
      glVertex3f(x + 0.5f, y + 0.5f, z);
      glTexCoord2d(0, 1);
      glVertex3f(x - 0.5f, y + 0.5f, z);
      glTexCoord2d(1, 0);
      glVertex3f(x + 0.5f, y - 0.5f, z);
      glTexCoord2d(0, 0);
      glVertex3f(x - 0.5f, y - 0.5f, z);
      glEnd();

      particle[loop_].x += particle[loop_].xi / (slowdown * 1000);
      particle[loop_].y += particle[loop_].yi / (slowdown * 1000);
      particle[loop_].z += particle[loop_].zi / (slowdown * 1000);

      particle[loop_].xi += particle[loop_].xg;
      particle[loop_].yi += particle[loop_].yg;
      particle[loop_].zi += particle[loop_].zg;
      particle[loop_].life -= particle[loop_].fade;
      glUniform1f(fadeEffect_, particle[loop_].life);

      if (particle[loop_].life < 0.0f) {
        particle[loop_].life = 0.0f;
        particle[loop_].fade = float(rand() % 100) / 1000.0f + 0.003f;
        particle[loop_].xi = xspeed + float((rand() % 60) - 32.0f);
        particle[loop_].yi = yspeed + float((rand() % 60) - 30.0f);
        particle[loop_].zi = float((rand() % 60) - 30.0f);
        faded = true;
      }
    }
  }
  disableRender();
}
