#ifndef PARTICLES_H
#define PARTICLES_H
#pragma once

#include "SceneObject.hpp"

class Particles : public SceneObject {

  public:
  Particles(glm::mat4& m);
  bool allFaded{ false };
  //~Particles();

  protected:
  virtual void privateInit();
  virtual void privateRender();
  virtual void privateUpdate();

  private:
  static constexpr int MAX_PARTICLES{ 800 };

  bool keys[256];
  bool active{ true };
  bool fullscreen = true;
  bool rainbow = true;

  float slowdown = 2.0f;
  float xspeed;
  float yspeed;
  float zoom = 0.0f;

  GLuint loop_;
  GLuint col_;
  GLuint delay_;
  GLuint partTex_;
  Shader particleEffect_;
  glm::vec4 colorsToShader_;
  GLint fadeEffect_;

  const GLfloat colors[12][3] = {
    { 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
    { 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
    { 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
  };

  typedef struct
  {
    bool active;
    float life;
    float fade;
    float r;
    float g;
    float b;
    float x;
    float y;
    float z;
    float xi;
    float yi;
    float zi;
    float xg;
    float yg;
    float zg;
  } particleContainer;
  particleContainer particle[MAX_PARTICLES];
  void prepareRender();
  void disableRender();
};

#endif
