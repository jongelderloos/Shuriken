#include "PhysSpace2D.h"
#include <iostream>

using namespace std;

PhysSpace2D::PhysSpace2D()
{
  height = 1;
  width = 1;
}

PhysSpace2D::PhysSpace2D(float h, float w)
{
  init(h, w);
}

PhysSpace2D::PhysSpace2D(float h, float w, vector<PhysObj2D*> obj)
{
  init(h, w, obj);
}

void PhysSpace2D::init(float h, float w)
{
  height = h;
  width = w;
}

void PhysSpace2D::init(float h, float w, vector<PhysObj2D*> obj)
{
  height = h;
  width = w;
  objects = obj;
}

void PhysSpace2D::addObject(PhysObj2D* obj)
{
  try
  {
    objects.push_back(obj);
  }
  catch(const std::bad_alloc& e)
  {
    cout << "Bad alloc error: " << e.what();
  }
}

void PhysSpace2D::removeObject(PhysObj2D* obj)
{
  for(auto curObj : objects)
  {
    auto idx = &curObj - &objects[0];
    if(obj == curObj)
    {
      try
      {
        objects.erase(objects.begin() + idx );
      }
      catch(const std::out_of_range& e)
      {
        cout << "Out of range error: " << e.what();
      }
      break;
    }
  }
}

void PhysSpace2D::tick()
{
  bool hasCollided = false;

  for(auto obj : objects)
  {
    if(obj->canMove)
    {
      //obj->nextPos.x = obj->pos.x + (obj->vel.x / TICKS_PER_SECOND);
      //obj->nextPos.y = obj->pos.y + (obj->vel.y / TICKS_PER_SECOND);
      //cout << "Object: " << obj->name << " next pos: (" << obj->pos.x << "," << obj->pos.y << ")";
      //cout << "Velocity: (" << obj->vel.x << "," << obj->vel.y << ")";
    }

    if(obj->feelsGravity)
    {
      // TODO: add grav code
    }
  }

  for(auto obj : objects)
  {
    if(obj->canCollide)
    {
      // TODO: aparently you cant use auto within auto on the same list otherwise it gives const
      // look into this
      
      //for(auto compObj : objects)
      for( unsigned int i = 0; i < objects.size(); i++ )
      {
        if(obj != objects[i])
        {
          if(objects[i]->canCollide)
          {
            hasCollided = obj->hitBox.checkCollision(objects[i]->hitBox);

            if(hasCollided)
            {
              // TODO: this does not work right now
              obj->handleCollision(objects[i]);
            }
          }
        }
      }
    }
  }

  for(auto obj : objects)
  {
    if(!obj->collisions.empty())
    {
      obj->resolveCollisions();
    }
  }
}
