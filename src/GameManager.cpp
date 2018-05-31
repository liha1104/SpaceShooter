#include "include/GameManager.hpp"
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

  //Light position
  float lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  // Adding the camera to the scene
  cam_.reset(new Camera());

  skybox_.reset(new Skybox());
  this->addSubObject(skybox_);

  auto skyboxMat = skybox_->getMatrix();
  auto camMat = cam_->getMatrix();

  auto transVec4 = camMat[3] - skyboxMat[3];

  auto transVec3 = glm::vec3(-transVec4.x, -transVec4.y, -transVec4.z);

  skybox_->setMatrix(glm::translate(skyboxMat, transVec3));

  bf_.reset(new BattleField());
  this->addSubObject(bf_);
  bf_->getMatrix()[3].x = bf_->getMatrix()[3].z - 310;

  bf2_.reset(new BattleField());
  this->addSubObject(bf2_);
  bf2_->getMatrix()[3].x = bf2_->getMatrix()[3].z - 310;
  bf2_->getMatrix()[3].z -= 5120;

  water_.reset(new Water());
  this->addSubObject(water_);

  spaceshipm_.reset(new SpaceShipModel());
  this->addSubObject(spaceshipm_);
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

  eternalBF();


  bool sd = false;
  bool c = false;
  for (auto en = enemies_.begin(); en != enemies_.end();) {

    if ((*en)->getType() == Enemy::type_::shooterzz)
      enemyShoots(*en);

    for (auto it = bullets_.begin(); it != bullets_.end();) {

      if (bullColl((*it)->getMatrix(), 3, spaceshipm_->getMatrix(), 15) && (*it)->getOwner() == Weapons::owner_::enemy) {
        sd = true;
        splosions((*it)->getMatrix());
        this->removeSubObject(*it);
        it = bullets_.erase(it);
        invulnerability(spaceshipm_);
      }
      else if (((*it)->getMatrix()[3].z >= -1100 && !bullColl((*it)->getMatrix(), 3, (*en)->getMatrix(), 6))
          || (bullColl((*it)->getMatrix(), 3, (*en)->getMatrix(), 10) && (*it)->getOwner() == Weapons::owner_::enemy)) {
        it++;
        continue;
      }
      else if ((*it)->getMatrix()[3].z <= -1100 || (*it)->getMatrix()[3].z >= 0) {
        this->removeSubObject(*it);
        bullets_.erase(it);
        break;
      }
      else if (bullColl((*it)->getMatrix(), 5, (*en)->getMatrix(), 15) && (*it)->getOwner() == Weapons::owner_::ship) {
        splosions((*it)->getMatrix());
        this->removeSubObject(*it);
        it = bullets_.erase(it);
        c = true;
        break;
      }
    }

    if (sd && (*spaceshipm_).getLife() == 0) {
      splosions(spaceshipm_->getMatrix());
      this->removeSubObject(spaceshipm_);
    }

    if (!c && !shipColl(spaceshipm_->getMatrix(), 5, (*en)->getMatrix(), 6)) {
      en++;
      continue;
    }
    else if (c) {
      splosions((*en)->getMatrix());
      this->removeSubObject(*en);
      enemies_.erase(en);
      break;
    }
    else if (shipColl(spaceshipm_->getMatrix(), 5, (*en)->getMatrix(), 6)) {
      splosions(spaceshipm_->getMatrix());
      this->removeSubObject(spaceshipm_);
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

std::shared_ptr<SpaceShipModel> GameManager::getShipM()
{
  return spaceshipm_;
}

void GameManager::setWeapon(Weapons::type_ sw)
{
  shipWeapon_ = sw;
}

void GameManager::invulnerability(std::shared_ptr<SpaceShipModel> s)
{
  if (std::chrono::system_clock::now() > endwait4) {
    s->reduceLife();
    endwait4 = std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
  }
}

void GameManager::splosions(glm::mat4 pos){
  std::shared_ptr<Particles> new_explosion;
        new_explosion.reset(new Particles(pos));
        particles_.push_back(new_explosion);
        this->addSubObject(new_explosion);
        new_explosion->getMatrix()[3] = (pos[3]);
        if (particles_.size() > 2)
        {
          this->removeSubObject(*particles_.begin());
          particles_.erase(particles_.begin());
        }
}


void GameManager::bulletFired()
{
  if (std::chrono::system_clock::now() > endwait) {
    if (shipWeapon_ == Weapons::type_::bullet) {
      weapon_.reset(new Weapons());
      this->addSubObject(weapon_);
      weapon_->setOwner(Weapons::owner_::ship);
      weapon_->setType(shipWeapon_);
      bullets_.push_back(weapon_);
      weapon_->getMatrix()[3].x = spaceshipm_->getMatrix()[3].x;
      weapon_->getMatrix()[3].y = spaceshipm_->getMatrix()[3].y;
      weapon_->getMatrix()[3].z = spaceshipm_->getMatrix()[3].z;
      endwait = std::chrono::system_clock::now() + std::chrono::milliseconds(150);
    }
    else if (shipWeapon_ == Weapons::type_::rocket) {
      weaponR_.reset(new Weapons());
      this->addSubObject(weaponR_);
      weaponR_->setOwner(Weapons::owner_::ship);
      weaponR_->setType(shipWeapon_);
      bullets_.push_back(weaponR_);
      weaponL_.reset(new Weapons());
      this->addSubObject(weaponL_);
      weaponL_->setOwner(Weapons::owner_::ship);
      weaponL_->setType(shipWeapon_);
      bullets_.push_back(weaponL_);
      weaponR_->getMatrix()[3].x = spaceshipm_->getMatrix()[3].x + 15;
      weaponR_->getMatrix()[3].y = spaceshipm_->getMatrix()[3].y;
      weaponR_->getMatrix()[3].z = spaceshipm_->getMatrix()[3].z;
      weaponL_->getMatrix()[3].x = spaceshipm_->getMatrix()[3].x - 15;
      weaponL_->getMatrix()[3].y = spaceshipm_->getMatrix()[3].y;
      weaponL_->getMatrix()[3].z = spaceshipm_->getMatrix()[3].z;
      endwait = std::chrono::system_clock::now() + std::chrono::milliseconds(500);
    }
  }
}

void GameManager::eternalBF()
{
  if (bf_->getMatrix()[3].z >= 5120)
    bf_->getMatrix()[3].z -= 5120 * 2;
  if (bf2_->getMatrix()[3].z >= 5120)
    bf2_->getMatrix()[3].z -= 5120 * 2;
}


void GameManager::generateEnemy()
{
  double r = rand() % 230 - 115;
  if (std::chrono::system_clock::now() > endwait2) {
    enemy_.reset(new Enemy());
    this->addSubObject(enemy_);
    enemies_.push_back(enemy_);
    enemy_->init();
    enemy_->getMatrix()[3].x = r;
    endwait2 = std::chrono::system_clock::now() + std::chrono::milliseconds(2200);
  }
}

void GameManager::enemyShoots(std::shared_ptr<Enemy> e)
{
  if (std::chrono::system_clock::now() > e->getTime()) {
    weapon_.reset(new Weapons());
    this->addSubObject(weapon_);
    weapon_->setOwner(Weapons::owner_::enemy);
    bullets_.push_back(weapon_);
    weapon_->getMatrix()[3].x = e->getMatrix()[3].x;
    weapon_->getMatrix()[3].y = e->getMatrix()[3].y;
    weapon_->getMatrix()[3].z = e->getMatrix()[3].z;
    //weapon_->getMatrix() = e->getMatrix();
    e->setTime(std::chrono::system_clock::now() + std::chrono::milliseconds(700));
  }
}

bool GameManager::bullColl(glm::mat4 w, double r1, glm::mat4 e, double r2)
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

bool GameManager::shipColl(glm::mat4 s, double r1, glm::mat4 e, double r2)
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
