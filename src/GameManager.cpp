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

  //PlaySound("C:\\Users\\Victor\\Documents\\VS17 Projects\\AlienElimination\\AlienElimination\\src\\loop.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);


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

  boolean sd = false;
  for (auto en = enemies_.begin(); en != enemies_.end();) {

    if ((*en)->getType() == Enemy::type_::shooterzz)
      enemyShoots(*en);
    boolean c = false;

    for (auto it = bullets_.begin(); it != bullets_.end();) {


      if (bullColl((*it)->getMatrix(), 3, spaceship_->getMatrix(), 6) && (*it)->getOwner() == Weapons::owner_::enemy) {
        sd = true;
        invulnerability(spaceship_);
      }
      if ((*it)->getMatrix()[3].z >= -1100 && !bullColl((*it)->getMatrix(), 3, (*en)->getMatrix(), 6) 
        || (bullColl((*it)->getMatrix(), 3, (*en)->getMatrix(), 6) && (*it)->getOwner() == Weapons::owner_::enemy)) {
        it++;
        continue;
      }
      else if ((*it)->getMatrix()[3].z <= -1100 || (*it)->getMatrix()[3].z >= 0) {
        this->removeSubObject(*it);
        bullets_.erase(it);
        break;
      }
      else if (bullColl((*it)->getMatrix(), 3, (*en)->getMatrix(), 6) && (*it)->getOwner() == Weapons::owner_::ship) {
        this->removeSubObject(*it);
        bullets_.erase(it);
        c = true;
        break;
      }
    }

    if (sd && (*spaceship_).getLife() == 0) {
      this->removeSubObject(spaceship_);
    }

    if (!c && !shipColl(spaceship_->getMatrix(), 5, (* en)->getMatrix(), 6)) {
      en++;
      continue;
    }
    else if (c) {
      this->removeSubObject(*en);
      enemies_.erase(en);
      break;
    }
    else if (shipColl(spaceship_->getMatrix(), 5, (*en)->getMatrix(), 6)) {
      this->removeSubObject(spaceship_);
      this->removeSubObject(*en);
      enemies_.erase(en);
      break;
    }
    
  }  
  generateEnemy();
}


std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}

std::shared_ptr<SpaceShip> GameManager::getShip()
{
  return spaceship_;
}

void GameManager::setWeapon(Weapons::type_ sw)
{
  shipWeapon_ = sw;
}

void GameManager::invulnerability(std::shared_ptr<SpaceShip> s)
{
  if (clock() > endwait4) {
  s->reduceLife();
  endwait4 = clock() + 1 * CLOCKS_PER_SEC;
  }
}

void GameManager::bulletFired()
{
  if(clock() > endwait){
    weapon_.reset(new Weapons());
    this->addSubObject(weapon_);
    weapon_->setOwner(Weapons::owner_::ship);
    weapon_->setType(shipWeapon_);
    bullets_.push_back(weapon_);
    weapon_->getMatrix() = spaceship_->getMatrix();
    if (weapon_->getType() == Weapons::type_::bullet)
    endwait = clock() + 0.3 * CLOCKS_PER_SEC;
    else if (weapon_->getType() == Weapons::type_::rocket)
      endwait = clock() + 0.7 * CLOCKS_PER_SEC;
  }
}

void GameManager::generateEnemy()
{
  double r = rand() % 230 - 115;
  if (clock() > endwait2) {
    enemy_.reset(new Enemy());
    this->addSubObject(enemy_);
    enemies_.push_back(enemy_);
    enemy_->init();
    enemy_->getMatrix()[3].x = r;
    endwait2 = clock() + 1 * CLOCKS_PER_SEC;
  }
}

void GameManager::enemyShoots(std::shared_ptr<Enemy> e)
{
  if (clock() > e->endwait3) {
    weapon_.reset(new Weapons());
    this->addSubObject(weapon_);
    weapon_->setOwner(Weapons::owner_::enemy);
    bullets_.push_back(weapon_);
    weapon_->getMatrix() = e->getMatrix();
    e->endwait3 = clock() + 1 * CLOCKS_PER_SEC;
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


