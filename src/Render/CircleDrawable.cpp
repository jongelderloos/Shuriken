#include "CircleDrawable.h"
#include <stdint.h>
#include <cmath>

CircleDrawable::CircleDrawable()
{
  xCoord = 0;
  yCoord = 0;
  radius = 1;
}

CircleDrawable::CircleDrawable(float x, float y, float radius)
{
  xCoord = x;
  yCoord = y;
  this->radius = radius;
}

void CircleDrawable::Render(void* videoMemPtr, int windowWidth, int windowHeight, int pixelsPerUnit)
{
  int xPixels = xCoord * pixelsPerUnit;
  int yPixels = yCoord * pixelsPerUnit;
  int radiusPixels = radius * pixelsPerUnit;

  uint8_t* row = (uint8_t*)videoMemPtr;
  row += ((yPixels-radiusPixels)*windowWidth*4);
  for(int y = 0; y <= (radiusPixels*2); y++)
  {
    uint32_t* pixel = (uint32_t*)row;
    pixel += (xPixels-radiusPixels);
    for(int x = 0; x <= (radiusPixels*2); x++)
    {
      if(pixel >= (uint32_t*)videoMemPtr && pixel <= (uint32_t*)videoMemPtr + ((windowWidth * windowHeight) * 4))
      {
        float xDist = abs((float)radiusPixels - (float)x);
        float yDist = abs((float)radiusPixels - (float)y);

        float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

        if((int)round(dist) <= radiusPixels)
        {
          *pixel++ = color;
        }
        else
        {
          pixel++;
        }
      }
    }
    row += windowWidth * 4;
  }
}
