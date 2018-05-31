#pragma once

#include "BattleField.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"
#include "SceneObject.hpp"
#include "SpaceShip.hpp"
#include "Weapons.hpp"
#include "Skybox.hpp"
#include "Water.hpp"
#include "SpaceShipModel.hpp"
#include "Particles.hpp"
#include <chrono>

class GameManager : public SceneObject {
  public:
  GameManager();
  ~GameManager();

  std::shared_ptr<Camera> getCam();
  std::shared_ptr<SpaceShip> getShip();
  std::shared_ptr<SpaceShipModel> getShipM();
  void setWeapon(Weapons::type_);
  void bulletFired();
  void eternalBF();
  void generateEnemy();
  void enemyShoots(std::shared_ptr<Enemy>);
  bool bullColl(glm::mat4, double, glm::mat4, double);
  bool shipColl(glm::mat4, double, glm::mat4, double);
  void invulnerability(std::shared_ptr<SpaceShipModel>);
  void splosions(glm::mat4);

  protected:
  virtual void privateInit();
  virtual void privateRender();
  virtual void privateUpdate();

  private:
  std::vector<std::shared_ptr<Particles>> particles_;
  std::vector<std::shared_ptr<Weapons>> bullets_;
  std::vector<std::shared_ptr<Enemy>> enemies_;
  std::shared_ptr<BattleField> bf_;
  std::shared_ptr<BattleField> bf2_;
  std::shared_ptr<SpaceShip> spaceship_;
  std::shared_ptr<SpaceShipModel> spaceshipm_;
  std::shared_ptr<Enemy> enemy_;
  std::shared_ptr<Camera> cam_;
  std::shared_ptr<Weapons> weapon_;
  std::shared_ptr<Weapons> weaponR_;
  std::shared_ptr<Weapons> weaponL_;
  std::shared_ptr<Skybox> skybox_;
  std::shared_ptr<Water> water_;

  Weapons::type_ shipWeapon_ = Weapons::type_::bullet;

  std::chrono::_V2::system_clock::time_point endwait = std::chrono::system_clock::now();
  std::chrono::_V2::system_clock::time_point endwait2 = std::chrono::system_clock::now();
  //clock_t endwait3 = clock();
  std::chrono::_V2::system_clock::time_point endwait4 = std::chrono::system_clock::now();
};
