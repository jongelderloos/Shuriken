#ifndef _PHYSSPACE2D_H_
#define _PHYSSPACE2D_H_

#include <vector>
#include "PhysObj2D.h"

using std::vector;

#define TICKS_PER_SECOND 60

class __declspec(dllexport) PhysSpace2D
{
public:
  PhysSpace2D();
  PhysSpace2D(float h, float w);
  PhysSpace2D(float h, float w, vector<PhysObj2D*> obj);
  void init(float h, float w);
  void init(float h, float w, vector<PhysObj2D*> obj);
  void addObject(PhysObj2D* obj);
  void removeObject(PhysObj2D* obj);
  void tick();
  float height;
  float width;
  vector<PhysObj2D*> objects;
};

#endif //_PHYSSPACE2D_H_
