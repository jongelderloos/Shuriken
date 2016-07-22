#ifndef _PADDLEDRAWABLE_H_
#define _PADDLEDRAWABLE_H_

#include "Drawable2D.h"
#include <stdint.h>

class __declspec(dllexport) PaddleDrawable : public Drawable2D
{
public:
  PaddleDrawable();
  PaddleDrawable(int, int, int, int);
  void Render(void*, int, int) override;
  int xCoord;
  int yCoord;
  int width;
  int height;
  uint32_t color;

private:
};



#endif //_PADDLEDRAWABLE_H_
