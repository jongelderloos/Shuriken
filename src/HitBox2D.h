#ifndef _HITBOX2D_H_
#define _HITBOX2D_H_

#include "Shape2D.h"

class __declspec(dllexport) HitBox2D
{
public:
  HitBox2D();
  HitBox2D(Shape2D b1);
  HitBox2D(Shape2D b1, Shape2D b2);
  bool checkCollision(HitBox2D& other);
  bool check1;
  Shape2D box1;
  bool check2;
  Shape2D box2;
};

#endif //_HITBOX2D_H_
