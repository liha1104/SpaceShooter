#include "include/FpsCounter.hpp"
#include "include/GameManager.hpp"
#include "include/Input.hpp"
#include "include/Text.hpp"
#include <GL/freeglut.h>
#include <chrono>
#include <sstream>
#include <thread>

#include <iostream>

std::shared_ptr<GameManager> gm;
siut::FpsCounter counter;

int window;

bool keyPressed[30];
int mousePosX, mousePosY;
Text _text;
int highScore = 0;

void init()
{
  glewInit();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  gm.reset(new GameManager());
  gm->init();
  _text.init();
  for (int i = 0; i < 30; i++)
    keyPressed[i] = false;
}

void printText()
{
  // Draw the text
  char buffer[800];
  glColor3f(1.0, 1.0, 0.8);
  glPushMatrix();
  glLoadIdentity();
  float xPosition = 35.0f;
  float xPositionControl = 30.0f;
  float yPosition = 25.0f;
  float lineShift = 2.0f;
  float zPosition = -50.0f;
  // Write text:

  std::stringstream ss;
  ss << "W: Forward, A: Left, S: Backward, D: Right";
  strcpy(buffer, ss.str().c_str());
  _text.setPos(xPositionControl, yPosition, zPosition);
  _text.printString(buffer, Text::FONT_NORMAL);

  ss = std::stringstream();
  ss << "Space: Shoot, 1: Primary, 2: Secondary";
  strcpy(buffer, ss.str().c_str());
  _text.setPos(xPositionControl, yPosition - 1 * lineShift, zPosition);
  _text.printString(buffer, Text::FONT_NORMAL);

  glColor3f(1.0, 1.0, 0.8);
  ss = std::stringstream();
  ss << "High Score: " << highScore;
  strcpy(buffer, ss.str().c_str());
  _text.setPos(-50, 25, -50);
  _text.printString(buffer, Text::FONT_NORMAL);

  glColor3f(1.0, 0.7, 0.0);
  ss = std::stringstream();
  ss << "Enemies defeated: " << gm->kills;
  strcpy(buffer, ss.str().c_str());
  _text.setPos(-5, 23, -50);
  _text.printString(buffer, Text::FONT_NORMAL);

  glColor3f(0.0, 1.0, 0.5);
  ss = std::stringstream();
  ss << "HP: " << gm->getShipM()->getLife();
  strcpy(buffer, ss.str().c_str());
  _text.setPos(-1.5, -25, -50);
  _text.printString(buffer, Text::FONT_NORMAL);

  glPopMatrix();
}

void gameOver()
{

  std::cout << "Resetting game" << std::endl;
  if (gm->kills > highScore)
    highScore = gm->kills;
  gm.reset(new GameManager());
  gm->init();
  _text.init();
  for (int i = 0; i < 30; i++)
    keyPressed[i] = false;
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gm->update(counter.fps());
  gm->render();

  if (keyPressed[KEY_ID_W] == true)
    gm->getShipM()->moveForward();
  if (keyPressed[KEY_ID_A] == true)
    gm->getShipM()->moveLeft();
  if (keyPressed[KEY_ID_D] == true)
    gm->getShipM()->moveRight();
  if (keyPressed[KEY_ID_S] == true)
    gm->getShipM()->moveBackward();
  if (keyPressed[KEY_ID_SPACE] == true)
    gm->bulletFired();
  if (keyPressed[KEY_ID_C] == true)
    gm->getShipM()->moveDown();
  if (keyPressed[KEY_ID_1] == true)
    gm->setWeapon(Weapons::type_::bullet);
  if (keyPressed[KEY_ID_2] == true)
    gm->setWeapon(Weapons::type_::rocket);

  if (gm->getShipM()->getLife() == 0)
    gameOver();
  else
    printText();

  glutSwapBuffers();
  glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 27:
    glutDestroyWindow(window);
#ifndef _WIN32
    // Must use this with regular glut, since it never returns control to main().
    exit(0);
#endif
    break;

  case 'w':
    keyPressed[KEY_ID_W] = true;
    break;
  case 'a':
    keyPressed[KEY_ID_A] = true;
    break;
  case 's':
    keyPressed[KEY_ID_S] = true;
    break;
  case 'd':
    keyPressed[KEY_ID_D] = true;
    break;
  case ' ':
    keyPressed[KEY_ID_SPACE] = true;
    break;
  case 'c':
    keyPressed[KEY_ID_C] = true;
    break;
  case '1':
    keyPressed[KEY_ID_1] = true;
    break;
  case '2':
    keyPressed[KEY_ID_2] = true;
    break;

  default:
    glutPostRedisplay();
  }
}

void keyUp(unsigned char key, int x, int y)
{
  switch (key) {
  case 'w':
    keyPressed[KEY_ID_W] = false;
    break;
  case 'a':
    keyPressed[KEY_ID_A] = false;
    break;
  case 's':
    keyPressed[KEY_ID_S] = false;
    break;
  case 'd':
    keyPressed[KEY_ID_D] = false;
    break;
  case ' ':
    keyPressed[KEY_ID_SPACE] = false;
    break;
  case 'c':
    keyPressed[KEY_ID_C] = false;
    break;
  case '1':
    keyPressed[KEY_ID_1] = false;
    break;
  case '2':
    keyPressed[KEY_ID_2] = false;
    break;
  }
}

void mousePressed(int button, int state, int posX, int posY)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    mousePosX = posX;
    mousePosY = posY;
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
  if (keyPressed[MOUSE_LEFT_BUTTON_DOWN]) {
    int diffX = posX - mousePosX;
    mousePosX = posX;
    int diffY = posY - mousePosY;
    mousePosY = posY;

    // Implement quaternion based mouse move
  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glOrtho(-50, 700, -50, 700, -50, 50);
  gluPerspective(60.0f, float(w) / float(h), 0.1f, 1300.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //  gluLookAt(0.0, 0.0, 10.0,     0.0, 0.0, 0.0,    0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(700, 700);
  glutInitWindowPosition(10, 10);
  window = glutCreateWindow("Space Shooter 3D");
  init();
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMouseFunc(mousePressed);
  glutMotionFunc(mouseMoved);

  // Add other callback functions here..

  glutMainLoop();
  return 0;
}
