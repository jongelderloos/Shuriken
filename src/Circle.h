#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Point2D.h"
#include "Shape2D.h"

class Box;

class __declspec(dllexport) Circle : public Shape2D
{
public:
  Circle();
  Circle(float, float);
  Circle(float, float, float);
  Circle operator=(const Circle& other);
  bool checkCollision(Shape2D* other) override;
  bool checkCollision(Circle* other) override;
  bool checkCollision(Box* other) override;
  float radius;
};

#endif //_CIRCLE_H_
