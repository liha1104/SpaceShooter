#pragma once

#include <windows.h>
#include <C:/Users/Victor/Documents/glew-2.1.0/glew-2.1.0/include/GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>  

#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Enemy.hpp"
#include "Weapons.hpp"
#include "Camera.hpp"
//#include "Clock.hpp"


class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
    std::shared_ptr<SpaceShip> getShip();
    void bulletFired();
    boolean bullColl(glm::mat4, double, glm::mat4, double);
    boolean shipColl(glm::mat4, double, glm::mat4, double);

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    std::vector<std::shared_ptr<Weapons>> bullets_;
    std::vector<std::shared_ptr<Enemy>> enemies_;
    std::shared_ptr<BattleField> bf_;
    std::shared_ptr<SpaceShip> spaceship_;
    std::shared_ptr<Enemy> enemy_;
    std::shared_ptr<Camera> cam_;
    std::shared_ptr<Weapons> weapon_;
    clock_t endwait;
    //siut::Clock clock_;
};

