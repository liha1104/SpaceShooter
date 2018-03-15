#pragma once

#include <windows.h>
#include <C:/Users/Victor/Documents/glew-2.1.0/glew-2.1.0/include/GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SOIL.h"

#include "SceneObject.hpp"
#include "../glm/glm/glm.hpp"

class BattleField : public SceneObject
{
	public:
		BattleField();
		~BattleField();

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();
    void loadTex();

	private:
    std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
    std::vector< UINT > indexArray_;
    std::vector<glm::vec2> texArray_;
    GLuint tex_2d;
    // normal array.
    // texture coord array
};

