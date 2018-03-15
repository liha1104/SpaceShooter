#pragma once

#include <windows.h>
#include <C:/Users/Victor/Documents/glew-2.1.0/glew-2.1.0/include/GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "SceneObject.hpp"
#include <vector>

class Camera : public SceneObject
{
	public:
		Camera();
		~Camera();

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveBackward();
    void moveForward();
    
  protected:
    void privateInit();
		void privateRender();
		void privateUpdate();

	private:
  
};


