#include "../include/GameManager.hpp"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include <iostream>


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
  // Set default OpenGL states
  glEnable(GL_CULL_FACE);

  // Adding the camera to the scene
  cam_.reset(new Camera());
  //  this->addSubObject(cam_);
  //  matrix_.translate(0.0f, 0.0f, -99.0f);

  bf_.reset(new BattleField());
  this->addSubObject(bf_);
  bf_->getMatrix()[3].x = bf_->getMatrix()[3].z - 155;

  spaceship_.reset(new SpaceShip());
  this->addSubObject(spaceship_);

  enemy_.reset(new Enemy());
  enemies_.push_back(enemy_);
  this->addSubObject(enemy_);

}

void GameManager::privateRender()
{
  // Nothing to render
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "Error: " << gluErrorString(err) << std::endl;
	std::cout.flush();

}

void GameManager::privateUpdate()
{
  // Instead of adding all objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();

  for (auto en = enemies_.begin(); en != enemies_.end();) {
    boolean c = false;
    for (auto it = bullets_.begin(); it != bullets_.end();) {

      if ((*it)->getMatrix()[3].z >= -1100 && !bullColl((*it)->getMatrix(), 3, (*en)->getMatrix(), 6)) {
        it++;
        continue;
      }

      else if ((*it)->getMatrix()[3].z <= -1100){
        this->removeSubObject(*it);
        bullets_.erase(it);
        break;
      }
      else if (bullColl((*it)->getMatrix(), 3, (*en)->getMatrix(), 6)) {
        this->removeSubObject(*it);
        bullets_.erase(it);
        c = true;
        break;
      }
    }
    if (!c)
      en++;
    else if (c) {
      this->removeSubObject(*en);
      enemies_.erase(en);
      break;
    }
 /*   else if (!shipColl(spaceship_->getMatrix(), 6, (*en)->getMatrix(), 6))
      en++;
    else if (shipColl(spaceship_->getMatrix(), 6, (*en)->getMatrix(), 6)) {
      this->removeSubObject(spaceship_);
      this->removeSubObject(*en);
      enemies_.erase(en);
      break;
    }*/


  }



}


std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}

std::shared_ptr<SpaceShip> GameManager::getShip()
{
  return spaceship_;
}


void GameManager::bulletFired()
{
  if(clock() > endwait){
    weapon_.reset(new Weapons());
    this->addSubObject(weapon_);
    bullets_.push_back(weapon_);
    weapon_->getMatrix() = spaceship_->getMatrix();
    endwait = clock() + 0.3 * CLOCKS_PER_SEC;
  }
}

boolean GameManager::bullColl(glm::mat4 w, double r1, glm::mat4 e, double r2)
{
  double d;
  double p1x = w[3].x;
  double p1y = w[3].y;
  double p1z = w[3].z;

  double p2x = e[3].x;
  double p2y = e[3].y;
  double p2z = e[3].z;

  d = sqrt(((p1x - p2x) * (p1x - p2x)) + ((p1y - p2y) * (p1y - p2y))
    + ((p1z - p2z) * (p1z - p2z)));

  if (d <= r2 + r1)
    return true;
  else
    return false;

}

boolean GameManager::shipColl(glm::mat4 s, double r1, glm::mat4 e, double r2)
{
  double d;
  double p1x = s[3].x;
  double p1y = s[3].y;
  double p1z = s[3].z;

  double p2x = e[3].x;
  double p2y = e[3].y;
  double p2z = e[3].z;

  d = sqrt(((p1x - p2x) * (p1x - p2x)) + ((p1y - p2y) * (p1y - p2y))
    + ((p1z - p2z) * (p1z - p2z)));

  if (d <= r2 + r1) {
    return true;
  }
  else
    return false;

}
