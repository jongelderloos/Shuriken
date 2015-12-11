#ifndef _POINT2D_H_
#define _POINT2D_H_

class __declspec(dllexport) Point2D
{
public:
  Point2D();
  Point2D(float, float);
  Point2D operator=(const Point2D&);
  float x;
  float y;
};

#endif //_POINT2D_H_
