#include "HitBox2D.h"
#include "Box.h"
#include <iostream>

using namespace std;

HitBox2D::HitBox2D()
{
  check1 = false;
  check2 = false;
}

HitBox2D::HitBox2D(Shape2D *b1)
{
  check1 = true;
  box1 = b1;
  check2 = false;
}

HitBox2D::HitBox2D(Shape2D *b1, Shape2D *b2)
{
  check1 = true;
  box1 = b1;
  check2 = true;
  box2 = b2;
}

bool HitBox2D::checkCollision(HitBox2D& other)
{
  bool collided = false;
  Box* thisHitBox = NULL;
  Box* otherHitBox = NULL;

  if(check1 && other.check1)
  {
    try
    {
      thisHitBox = (Box*)this->box1;
      otherHitBox = (Box*)other.box1;
    }
    catch(std::bad_cast& e)
    {
      cout << "Bad cast error: " << e.what();
    }

    collided = thisHitBox->checkCollision(*otherHitBox);
    
    if(collided && check2 && other.check2)
    {
      collided = thisHitBox->checkCollision(*otherHitBox);
    }
    // TODO: add cases for one object having a level2 bounding box
  }
  return collided;
}
