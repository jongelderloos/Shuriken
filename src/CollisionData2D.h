#ifndef _COLLISION_DATA2D_H_
#define _COLLISION_DATA2D_H_

#include "Vec2D.h"
#include "Point2D.h"

class CollisionData2D
{
public:
  CollisionData2D();
  CollisionData2D(Vec2D vel, Vec2D imp, Point2D p);
  bool operator==(const CollisionData2D& other);
  Vec2D velocity;
  Vec2D impulse;
  Point2D pos;
};

#endif //_COLLISION_DATA2D_H_
