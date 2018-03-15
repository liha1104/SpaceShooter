#pragma once

#include <windows.h>
#include <C:/Users/Victor/Documents/glew-2.1.0/glew-2.1.0/include/GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class Weapons : public SceneObject
{
public:
  Weapons();
  ~Weapons();

protected:
  void privateInit();
  void privateRender();
  void privateUpdate();

private:
  float speed_;

};
