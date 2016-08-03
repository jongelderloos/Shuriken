#include "PhysObj2D.h"
#include "Box.h"
#include <iostream>

using namespace std;

PhysObj2D::PhysObj2D()
{
  name = "";
  pos.x = 0;
  pos.y = 0;
  nextPos.x = 0;
  nextPos.y = 0;
  vel.x = 0;
  vel.y = 0;
  canMove = false;
  canCollide = false;
  feelsGravity = false;
  mass = 0;
}

PhysObj2D::PhysObj2D(std::string n, Point2D p, Vec2D v, HitBox2D hB, bool move, bool collide, bool grav, float m)
{
  init(n, p, v, hB, move, collide, grav, m);
}

void PhysObj2D::init(std::string n, Point2D p, Vec2D v, HitBox2D hB, bool move, bool collide, bool grav, float m)
{
  name = n;
  pos = p;
  nextPos.x = 0;
  nextPos.y = 0;
  vel = v;
  hitBox = hB;
  canMove = move;
  canCollide = collide;
  feelsGravity = grav;
  mass = m;
}

// TODO: this needs a major overhaul. I think the nextPos needs to go away and be
// replaced by last pos?
//
// This always uses box1 (a rectangle) to handle the collision
void PhysObj2D::handleCollision(PhysObj2D* other) throw (std::logic_error)
{
  Point2D pen; 
  float percentPen;
  float xDir = nextPos.x - pos.x;
  float yDir = nextPos.y - pos.y;
  Point2D hit; 
  Point2D newPos;
  float slope;
  float yIntercept;
  Vec2D impulse;
  CollisionData2D colData;
  Box* thisHitBox = NULL;
  Box* otherHitBox = NULL;

  try
  {
    thisHitBox = (Box*)this->hitBox.box1;
    otherHitBox = (Box*)other->hitBox.box1;
  }
  catch(std::bad_cast& e)
  {
    cout << "Bad cast error: " << e.what();
  }

  if((thisHitBox == NULL) || (otherHitBox == NULL))
  {
    return;
  }

  if(xDir > 0)
  {
    pen.x = (nextPos.x + thisHitBox->p2.x) - otherHitBox->p1.x;
  }
  else
  {
    pen.x = (nextPos.x + thisHitBox->p1.x) - otherHitBox->p2.x;
  }

  if(yDir > 0)
  {
    pen.y = (nextPos.y + thisHitBox->p2.y) - otherHitBox->p1.y;
  }
  else
  {
    pen.y = (nextPos.y + thisHitBox->p1.y) - otherHitBox->p2.y;
  }

  percentPen = pen.x / (nextPos.x - pos.x);

  newPos.x = nextPos.x - pen.x;
  newPos.y = nextPos.y - ((nextPos.y - pos.y) * percentPen);

  colData.pos = newPos;

  getPointSlope(&slope, &yIntercept);

  // The hit occured on the y axis
  if(newPos.y == ((slope * newPos.x) + yIntercept))
  {
    impulse.x = pen.x * -1;
    impulse.y = pen.y;
    colData.impulse = impulse;
    
    colData.velocity.x = vel.x * -1;
    colData.velocity.y = vel.y;
  }
  else
  {
    percentPen = pen.y / (nextPos.y - pos.y);

    newPos.x = nextPos.x - ((nextPos.x - pos.x) * percentPen);
    newPos.y = nextPos.y - pen.y;

    colData.pos = newPos;

    getPointSlope(&slope, &yIntercept);

    // The hit occured on the x axis
    if((newPos.y == ((slope * newPos.x) + yIntercept)) || (slope == INFINITY))
    {
      impulse.x = pen.x;
      impulse.y = pen.y * -1;
      colData.impulse = impulse;

      colData.velocity.x = vel.x;
      colData.velocity.y = vel.y * -1;
    }
    else
    {
      std::logic_error e("A collision was detected but could not be resolved");
      throw e; 
    }
  }
}

void PhysObj2D::resolveCollisions()
{
  Vec2D summedVel;
  Vec2D summedImp;
  Vec2D summedPos;
  int size = collisions.size();

  if(size == 1)
  {
    vel = collisions[0].velocity;

    pos.x = collisions[0].impulse.x + collisions[0].pos.x;
    pos.y = collisions[0].impulse.y + collisions[0].pos.y;
  }
  else if(size > 1)
  {
    for(auto col : collisions)
    {
      summedVel.x += col.velocity.x;
      summedVel.y += col.velocity.y;
      summedImp.x += col.impulse.x;
      summedImp.y += col.impulse.y;
      summedPos.x += col.pos.y;
      summedPos.y += col.pos.y;
    }

    vel.x = summedVel.x / size;
    vel.y = summedVel.y / size;
    
    pos.x = (summedImp.x / size) + (summedPos.x / size);
    pos.y = (summedImp.y / size) + (summedPos.y / size);
  }
}

void PhysObj2D::getPointSlope(float* slope, float* yIntercept)
{
  float rise;
  float run;

  rise = nextPos.y - pos.y;
  run = nextPos.x - pos.x;

  if(run == 0)
  {
    *slope = INFINITY;
  }
  else
  {
    *slope = rise / run;
  }

  *yIntercept = pos.y - *slope;
}

void PhysObj2D::addCollision(CollisionData2D* col)
{
  try
  {
    collisions.push_back(*col);
  }
  catch(const std::bad_alloc& e)
  {
    cout << "Bad alloc error: " << e.what();
  }
}

void PhysObj2D::removeCollision(CollisionData2D* col)
{
  for(auto curCol : collisions)
  {
    auto idx = &curCol - &collisions[0];
    if(*col == curCol)
    {
      try
      {
        collisions.erase(collisions.begin() + idx );
      }
      catch(const std::out_of_range& e)
      {
        cout << "Out of range error: " << e.what();
      }
      break;
    }
  }
}


