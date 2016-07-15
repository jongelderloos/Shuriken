#ifndef RENDER2D_H_
#define RENDER2D_H_

#include "Drawable2D.h"
#include <forward_list>

using std::forward_list;

class __declspec(dllexport) Render2D
{

public:
  Render2D();
  void setScreenCoords(int, int);
  void setScaleProperties(bool, bool);
  void setWindowSize(int, int);
  void addToForeground(Drawable2D*);
  void updateForeground(Drawable2D*);
  void removeForeground(Drawable2D*);
  void addToBackground(Drawable2D*);
  void updateBackground(Drawable2D*);
  void removeBackground(Drawable2D*);
  void setScreenBuffer(void*);
  void run();
  
private:
  bool scalable;
  bool lockedScaling;
  int coordWidth;
  int coordHeight;
  int windowWidth;
  int windowHeight;
  forward_list<Drawable2D*> background;
  forward_list<Drawable2D*> middleground;
  forward_list<Drawable2D*> foreground;
  //List<Drawable2D> priority;
  void* screenBuffer;
};

#endif // RENDER2D_H_
