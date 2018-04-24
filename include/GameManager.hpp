#pragma once

#include "BattleField.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"
#include "SceneObject.hpp"
#include "SpaceShip.hpp"
#include "Weapons.hpp"
#include <time.h>

class GameManager : public SceneObject {
  public:
  GameManager();
  ~GameManager();

  std::shared_ptr<Camera> getCam();
  std::shared_ptr<SpaceShip> getShip();
  void setWeapon(Weapons::type_);
  void bulletFired();
  void generateEnemy();
  void enemyShoots(std::shared_ptr<Enemy>);
  bool bullColl(glm::mat4, double, glm::mat4, double);
  bool shipColl(glm::mat4, double, glm::mat4, double);
  void invulnerability(std::shared_ptr<SpaceShip>);

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
  Weapons::type_ shipWeapon_ = Weapons::type_::bullet;
  clock_t endwait = clock();
  clock_t endwait2 = clock();
  //clock_t endwait3 = clock();
  clock_t endwait4 = clock();
};
