#include "CircleDrawable.h"
#include <stdint.h>
#include <cmath>

CircleDrawable::CircleDrawable()
{
  xCoord = 0;
  yCoord = 0;
  radius = 1;
}

CircleDrawable::CircleDrawable(int x, int y, int radius)
{
  xCoord = x;
  yCoord = y;
  this->radius = radius;
}

void CircleDrawable::Render(void* videoMemPtr, int windowWidth, int windowHeight)
{
  uint8_t* row = (uint8_t*)videoMemPtr;
  row += ((yCoord-radius)*windowWidth*4);
  for(int y = 0; y <= (radius*2); y++)
  {
    uint32_t* pixel = (uint32_t*)row;
    pixel += (xCoord-radius);
    for(int x = 0; x <= (radius*2); x++)
    {
      if(pixel >= (uint32_t*)videoMemPtr && pixel <= (uint32_t*)videoMemPtr + ((windowWidth * windowHeight) * 4))
      {
        float xDist = abs((float)radius - (float)x);
        float yDist = abs((float)radius - (float)y);

        float dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

        if((int)round(dist) <= radius)
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
