#ifndef _TEXT_H_
#define _TEXT_H_

#include "Vector3.hpp"
#include <GL/gl.h>

class Text {
  private:
  void makeRasterFont(void);
  void FillBitmapChar(char index, GLubyte bitmap[]);

  int _curfont;

  sima::Vector3f _pos;
  GLuint _fontOffset[2];
  GLubyte _letters[2][128][13];

  public:
  Text();

  virtual ~Text();

  void setPos(float x, float y, float z) { _pos.setXYZ(x, y, z); }
  void setPos(sima::Vector3f pos) { _pos = pos; }
  void init();
  void printString(const char* s, int font = -1) const;

  int getFont() const
  {
    return _curfont;
  }
  void setFont(const int font)
  {
    _curfont = font;
  }

  float getCharWidth(int font = -1) const;

  static const int FONT_NORMAL; // Normal font is 8x13 pixels
  static const int FONT_SMALL; // Small font is 5x7 pixels
  //	static const int FONT_LARGE;		// Large font is 16x26 pixels
};

#endif // _TEXT_H_
