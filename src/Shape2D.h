#ifndef _SHAPE2D_H_
#define _SHAPE2D_H_

#include "Point2D.h"

class Box;
class Circle;

class __declspec(dllexport) Shape2D
{
public:
  Shape2D();
  Shape2D(float, float);
  virtual Shape2D operator=(const Shape2D& other);
  virtual bool checkCollision(Shape2D* other);
  virtual bool checkCollision(Box* other);
  virtual bool checkCollision(Circle* other);
  Point2D pos;
};

#endif //_SHAPE2D_H_
