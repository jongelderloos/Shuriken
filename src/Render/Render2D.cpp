#include "Render2D.h"

Render2D::Render2D()
{
  scalable = false;
  lockedScaling = false;
  coordWidth = 0;
  coordWidth = 0;
  windowWidth = 0;
  windowWidth = 0;
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

void Render2D::addToForeground(Drawable2D item)
{
  foreground.push_front(item);
}

void Render2D::updateForeground(Drawable2D item)
{
  forward_list<Drawable2D>::iterator findIter = std::find(foreground.begin(), foreground.end(), item);

  if(findIter != foreground.end())
  {
    foreground.emplace_after(findIter, item);
    foreground.remove(*findIter);
  }
}

void Render2D::remoreForeground(Drawable2D item)
{
  foreground.remove(item);
}

void Render2D::setScreenBuffer(void* ptr)
{
  screenBuffer = ptr;
}

void Render2D::run()
{
  for(auto item : foreground)
  {
    item.Render(screenBuffer, windowWidth);
  }
}

