#pragma once

#include <windows.h>
#include <C:/Users/Victor/Documents/glew-2.1.0/glew-2.1.0/include/GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include <time.h>  

class Enemy : public SceneObject
{
public:
  Enemy();
  ~Enemy();
  enum class type_ { shooterzz, normal, zigzag };
  type_ getType();
  clock_t endwait3;

protected:
  void privateInit();
  void privateRender();
  void privateUpdate();

private:
  type_ t;
  boolean dukdw = 1;
  float speed_;
  float life_;
  float armor_;


};

