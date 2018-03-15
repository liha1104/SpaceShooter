#pragma once

#include <windows.h>
#include <C:/Users/Victor/Documents/glew-2.1.0/glew-2.1.0/include/GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class SpaceShip : public SceneObject
{
	public:
		SpaceShip();
		~SpaceShip();
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
    void texturize();


	private:
	  float speed_;
    float life_;
    float armor_;
    
};

