#pragma once

#include "SceneObject.hpp"

class Weapons : public SceneObject {
  public:
  Weapons();
  ~Weapons();
  enum class owner_ {
    ship,
    enemy
  };
  enum class type_ {
    bullet,
    rocket
  };
  owner_ getOwner();
  type_ getType();
  void setOwner(owner_);
  void setType(type_);

  protected:
  void privateInit();
  void privateRender();
  void privateUpdate();

  private:
  owner_ o;
  float speed_;
  type_ t;
};
