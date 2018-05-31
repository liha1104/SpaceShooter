#ifndef PARTICLES_H
#define PARTICLES_H
#pragma once

#include "SceneObject.hpp"

class Particles : public SceneObject {

public:
  Particles(glm::mat4& matrixToExplodingObject);
  bool allFaded {false};
  //~Particles();

protected:
  virtual void privateInit();
  virtual void privateRender();
  virtual void privateUpdate();

private:
  bool	keys[256];			// Array Used For The Keyboard Routine
  bool	active {true};      // Window Active Flag Set To TRUE By Default
  bool	fullscreen=true;    // Fullscreen Flag Set To Fullscreen Mode By Default
  bool	rainbow=true;       // Rainbow Mode?

  float	slowdown=2.0f;      // Slow Down Particles
  float	xspeed;				// Base X Speed (To Allow Keyboard Direction Of Tail)
  float	yspeed;				// Base Y Speed (To Allow Keyboard Direction Of Tail)
  float	zoom=0.0f;        // Used To Zoom Out

  GLuint	loop;			// Misc Loop Variable
  GLuint	col;			// Current Color Selection
  GLuint	delay;			// Rainbow Effect Delay
  GLuint	partTex;		// Storage For Our Particle Texture
  Shader    particleEffect;
  glm::vec4 colorsToShader;
  GLint fadeEffect;
  static constexpr int MAX_PARTICLES {800};


  const GLfloat colors[12][3]=		// Rainbow Of Colors
  {
    {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
    {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
    {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
  };

  typedef struct					// Create A Structure For Particle
  {
    bool	active;					// Active (Yes/No)
    float	life;					// Particle Life
    float	fade;					// Fade Speed
    float	r;						// Red Value
    float	g;						// Green Value
    float	b;						// Blue Value
    float	x;						// X Position
    float	y;						// Y Position
    float	z;						// Z Position
    float	xi;						// X Direction
    float	yi;						// Y Direction
    float	zi;						// Z Direction
    float	xg;						// X Gravity
    float	yg;						// Y Gravity
    float	zg;						// Z Gravity
  }
  particleContainer;
  particleContainer particle[MAX_PARTICLES];
  void prepareRender();
  void disableRender();

};

#endif
