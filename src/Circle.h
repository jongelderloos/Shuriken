#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Point2D.h"
#include "Shape2D.h"

class __declspec(dllexport) Circle : public Shape2D
{
public:
  Circle();
  Circle(float, float);
  Circle(float, float, float);
  Circle operator=(const Circle&);
  float radius;
  Point2D center;
};

#endif //_CIRCLE_H_
