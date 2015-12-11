#ifndef _VEC2D_H_
#define _VEC2D_H_

class __declspec(dllexport) Vec2D
{
public:
  Vec2D();
  Vec2D(float xDir, float yDir);
  Vec2D operator=(const Vec2D& other);
  float x;
  float y;
};

#endif //_VEC2D_H_
