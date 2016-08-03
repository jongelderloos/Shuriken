#ifndef _BOX_H_
#define _BOX_H_

#include "Point2D.h"
#include "Shape2D.h"

class Circle;

class __declspec(dllexport) Box : public Shape2D
{
public:
  Box();
  Box(float, float);
  Box(float, float, float, float);
  Box operator=(const Box& other);
  bool checkCollision(Shape2D* other) override;
  bool checkCollision(Box* other) override;
  bool checkCollision(Circle* other) override;
  Point2D p1;
  Point2D p2;
};

#endif //_BOX_H_
