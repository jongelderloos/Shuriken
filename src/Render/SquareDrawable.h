#ifndef _SQUAREDRAWABLE_H_
#define _SQUAREDRAWABLE_H_

#include "Drawable2D.h"
#include <stdint.h>

class __declspec(dllexport) SquareDrawable : public Drawable2D
{
public:
  SquareDrawable();
  SquareDrawable(float, float, float, float);
  void Render(void*, int, int, int) override;
  float xCoord;
  float yCoord;
  float width;
  float height;
  uint32_t color;

private:
};



#endif //_PADDLEDRAWABLE_H_
