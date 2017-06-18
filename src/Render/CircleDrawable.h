#ifndef _CIRCLEDRAWABLE_H_
#define _CIRCLEDRAWABLE_H_

#include "Drawable2D.h"
#include <stdint.h>

class __declspec(dllexport) CircleDrawable : public Drawable2D
{
public:
  CircleDrawable();
  CircleDrawable(float, float, float);
  void Render(void*, int, int, int) override;
  float xCoord;
  float yCoord;
  float radius;
  uint32_t color;

private:
};



#endif //_CIRCLEDRAWABLE_H_
