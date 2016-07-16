#include "Render2D.h"
#include <algorithm>

Render2D::Render2D()
{
  scalable = false;
  lockedScaling = false;
  coordWidth = 0;
  coordHeight = 0;
  windowWidth = 0;
  windowHeight = 0;
  screenBuffer = NULL;
}

void Render2D::setScreenCoords(int width, int height)
{
  coordWidth = width;
  coordHeight = height;
}

void Render2D::setScaleProperties(bool isScalable, bool isLockedScaling = true)
{
  scalable = isScalable;
  lockedScaling = isLockedScaling;
}

void Render2D::setWindowSize(int width, int height)
{
  windowWidth = width;
  windowHeight = height;
}

void Render2D::addToForeground(Drawable2D *item)
{
  foreground.push_front(item);
}

void Render2D::updateForeground(Drawable2D *item)
{
  //forward_list<Drawable2D>::iterator findIter = std::find(foreground.begin(), foreground.end(), item);
  forward_list<Drawable2D*>::iterator findIter = std::find_if(foreground.begin(), foreground.end(), [item](Drawable2D *n){return n->id == item->id;});

  if(findIter != foreground.end())
  {
    //foreground.emplace_after(findIter, item);
    foreground.remove(*findIter);
    foreground.push_front(item);
  }
}

void Render2D::removeForeground(Drawable2D *item)
{
  //foreground.remove(item);
  foreground.remove_if([item](Drawable2D *n){return n->id == item->id;});
}

void Render2D::addToBackground(Drawable2D *item)
{
  background.push_front(item);
}

void Render2D::updateBackground(Drawable2D *item)
{
  //forward_list<Drawable2D>::iterator findIter = std::find(foreground.begin(), foreground.end(), item);
  forward_list<Drawable2D*>::iterator findIter = std::find_if(background.begin(), background.end(), [item](Drawable2D *n){return n->id == item->id;});

  if(findIter != background.end())
  {
    //background.emplace_after(findIter, item);
    background.remove(*findIter);
    background.push_front(item);
  }
}

void Render2D::removeBackground(Drawable2D *item)
{
  //background.remove(item);
  background.remove_if([item](Drawable2D *n){return n->id == item->id;});
}
void Render2D::setScreenBuffer(void* ptr)
{
  screenBuffer = ptr;
}

void Render2D::run()
{
  for(auto item : background)
  {
    item->Render(screenBuffer, windowWidth, windowHeight);
  }

  for(auto item : foreground)
  {
    item->Render(screenBuffer, windowWidth, windowHeight);
  }
}

