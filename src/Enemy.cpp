#include "include/Enemy.hpp"
#include "include/OBJLoader.hpp"
#include <iostream>
#include <math.h>
#include <random>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::privateInit()
{
  shader_.loadShaders("shaders/red.vert", "shaders/red.frag");
  objl::Loader Loader;
  bool loadout = Loader.LoadFile("src/arwing.obj");

  if (loadout) {
    for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {
      objl::Mesh curMesh = Loader.LoadedMeshes[i];
      for (int j = 0; j < curMesh.Vertices.size(); j++) {
        VERT_.push_back(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z));
        NORM_.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z));
        TEXC_.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
      }

      for (int j = 0; j < curMesh.Indices.size(); j += 3) {
        INDI_.push_back(curMesh.Indices[j]);
        INDI_.push_back(curMesh.Indices[j + 1]);
        INDI_.push_back(curMesh.Indices[j + 2]);
      }
    }
  }
  else {
    std::cout << "Could not load file!" << std::endl;
  }

  std::random_device gen;
  std::mt19937 eng(gen());
  std::uniform_int_distribution<int> dis(0, 2);
  int d = dis(eng);
  if (d == 0)
    t = type_::shooterzz;
  else if (d == 1)
    t = type_::normal;
  else
    t = type_::zigzag;

  matrix_ = glm::rotate(matrix_, 3.1415926535897932384626433832795f, glm::vec3(0, 1, 0));
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 1000.0f));
  matrix_ = glm::scale(matrix_, glm::vec3(10.0f, 10.0f, 10.0f));
}

void Enemy::privateRender()
{
  if (t == type_::shooterzz) {
    //glLoadIdentity();
    float diffMat[] = { 0.7f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffMat);

    float specMat[] = { 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specMat);
  }

  else if (t == type_::normal) {
    //glLoadIdentity();
    float diffMat[] = { 0.0f, 0.5f, 0.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffMat);

    float specMat[] = { 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specMat);
  }

  else {
    //glLoadIdentity();
    float diffMat[] = { 0.3f, 0.0f, 0.8f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffMat);

    float specMat[] = { 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specMat);
  }

  shader_.enableProgram();

  glDisable(GL_COLOR_MATERIAL);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glEnable(GL_PRIMITIVE_RESTART);

  glVertexPointer(3, GL_FLOAT, 0, &VERT_[0]);
  glNormalPointer(GL_FLOAT, 0, &NORM_[0]);

  glDrawElements(GL_TRIANGLES,
      INDI_.size(),
      GL_UNSIGNED_INT,
      &INDI_[0]);

  glDisable(GL_PRIMITIVE_RESTART);

  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  shader_.disableProgram();
}

void Enemy::privateUpdate()
{
  if (matrix_[3].x > 115)
    dukdw = 0;
  else if (matrix_[3].x < -115)
    dukdw = 1;

  if (t == type_::normal)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -0.3f));

  else {
    if (dukdw)
      matrix_ = glm::translate(matrix_, glm::vec3(-0.1f, 0.0f, -0.2));
    else
      matrix_ = glm::translate(matrix_, glm::vec3(0.1f, 0.0f, -0.2f));
  }
}

Enemy::type_ Enemy::getType()
{
  return t;
}

std::chrono::_V2::system_clock::time_point Enemy::getTime()
{
  return endwait3;
}

void Enemy::setTime(std::chrono::_V2::system_clock::time_point t)
{
  endwait3 = t;
}
