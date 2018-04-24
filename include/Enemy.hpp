#pragma once

#include "SceneObject.hpp"
#include <time.h>

class Enemy : public SceneObject {
  public:
  Enemy();
  ~Enemy();
  enum class type_ { shooterzz,
    normal,
    zigzag };
  type_ getType();
  clock_t endwait3 = clock();

  protected:
  void privateInit();
  void privateRender();
  void privateUpdate();

  private:
  type_ t;
  bool dukdw = 1;
  float speed_;
  float life_;
  float armor_;
};
