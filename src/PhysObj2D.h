#ifndef _PHYSOBJ2D_H_
#define _PHYSOBJ2D_H_

#include "Point2D.h"
#include "HitBox2D.h"
#include "CollisionData2D.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <typeinfo>

using std::vector;

class __declspec(dllexport) PhysObj2D
{
public:
  PhysObj2D();
  PhysObj2D(std::string n, Point2D p, Vec2D v, HitBox2D hB, bool move = false, bool collide = false, bool grav = false, float m = 0);
  virtual void init(std::string n, Point2D p, Vec2D v, HitBox2D hB, bool move = false, bool collide = false, bool grav = false, float m = 0);
  virtual void handleCollision(PhysObj2D* other, float ticksPerSecond) throw (std::logic_error);
  virtual void resolveCollisions();
  std::string name;
  Point2D pos;
  Point2D nextPos;
  Vec2D vel;
  bool canMove;
  bool canCollide;
  bool feelsGravity;
  float mass;
  HitBox2D hitBox;
  vector<CollisionData2D> collisions;
private:
  void getPointSlope(float* slope, float* yIntercept);
  void addCollision(CollisionData2D* col);
  void removeCollision(CollisionData2D* col);
};

#endif //_PHYSOBJ2D_H_
