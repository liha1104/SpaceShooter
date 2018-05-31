#include "include/SpaceShipModel.hpp"
#include "include/OBJLoader.hpp"

SpaceShipModel::SpaceShipModel()
{
}

SpaceShipModel::~SpaceShipModel()
{
}


void SpaceShipModel::reduceLife()
{
  life_ -= 1;
}

float SpaceShipModel::getLife()
{
  return life_;
}

void SpaceShipModel::privateInit()
{
  shipShader_.loadShaders("shaders/ship.vert", "shaders/ship.frag");

  _texture = SOIL_load_OGL_texture
  (
    "/home/liha1104/Projects/spaceshooter/textures/thunder.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  /* check for an error during the load process */
  if (0 == _texture)
  {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
  }

  objl::Loader Loader;
  bool loadout = Loader.LoadFile("/home/liha1104/Projects/spaceshooter/src/thunder.obj");

  if (loadout)
  {
    for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
    {
      objl::Mesh curMesh = Loader.LoadedMeshes[i];
      for (int j = 0; j < curMesh.Vertices.size(); j++)
      {
        _VERT.push_back(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z));
        _NORM.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z));
        _TEXC.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
      }

      for (int j = 0; j < curMesh.Indices.size(); j += 3)
      {
        _INDI.push_back(curMesh.Indices[j]);
        _INDI.push_back(curMesh.Indices[j+1]);
        _INDI.push_back(curMesh.Indices[j+2]);
      }

    }
  } else {
    std::cout << "Could not load file!" << std::endl;
  }

    matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -80.0f));
    matrix_ = glm::scale(matrix_, glm::vec3(0.2f, 0.2f, 0.2f));
}

//void SpaceShipModel::privateRender()
//{

//  float diffMat[] = {1.0f, 0.0f, 0.0f};
//  glMaterialfv(	GL_FRONT, GL_DIFFUSE, diffMat);

//  float specMat[] = {1.0f, 1.0f, 1.0f};
//  glMaterialfv(	GL_FRONT, GL_SPECULAR, specMat);
//  redShader_.enableProgram();
//  glDisable(GL_COLOR_MATERIAL);

//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_NORMAL_ARRAY);


//    glEnable(GL_PRIMITIVE_RESTART);

//    glVertexPointer(3, GL_FLOAT, 0, &_VERT[0]);
//    //glNormalPointer(3, GL_FLOAT, 0 , &_NORM[0]);
//    glNormalPointer(GL_FLOAT, 0, &_NORM[0]);

//    glDrawElements(GL_TRIANGLES,
//      _INDI.size(),
//      GL_UNSIGNED_INT,
//      &_INDI[0]);

//    glDisable(GL_PRIMITIVE_RESTART);

//    glDisableClientState(GL_NORMAL_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
//    redShader_.disableProgram();
//}


void SpaceShipModel::privateRender()
{
  shipShader_.enableProgram();

  glDisable(GL_COLOR_MATERIAL);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glEnable(GL_PRIMITIVE_RESTART);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glVertexPointer(3, GL_FLOAT, 0, &_VERT[0]);
  glTexCoordPointer(2, GL_FLOAT, 0, &_TEXC[0]);


  glDrawElements(GL_TRIANGLES,
    _INDI.size(),
    GL_UNSIGNED_INT,
    &_INDI[0]);

  glDisable(GL_PRIMITIVE_RESTART);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glActiveTexture(GL_TEXTURE0);
  glDisable(GL_TEXTURE_2D);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  shipShader_.disableProgram();
}

void SpaceShipModel::privateUpdate()
{
}

void SpaceShipModel::moveRight()
{
  if (matrix_[3].x < 110)
    matrix_ = glm::translate(matrix_, glm::vec3(7.0f, 0.0f, 0.0f));
}
void SpaceShipModel::moveLeft()
{
  if (matrix_[3].x > -110)
    matrix_ = glm::translate(matrix_, glm::vec3(-7.0f, 0.0f, 0.0f));
}
void SpaceShipModel::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -7.0f, 0.0f));
}
void SpaceShipModel::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 7.0f, 0.0f));
}
void SpaceShipModel::moveForward()
{
  if (matrix_[3].z > -200)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -7.0f));
}

void SpaceShipModel::moveBackward()
{
  if (matrix_[3].z < -45)
    matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 7.0f));
}

