#include "PaddleDrawable.h"
#include <stdint.h>

PaddleDrawable::PaddleDrawable()
{
  xCoord = 0;
  yCoord = 0;
}

PaddleDrawable::PaddleDrawable(int x, int y, int width, int height)
{
  xCoord = x;
  yCoord = y;
  this->width = width;
  this->height = height;
}

void PaddleDrawable::Render(void* videoMemPtr, int windowWidth, int windowHeight)
{
  //uint32_t value = 0xFFFFFF;

  uint8_t* row = (uint8_t*)videoMemPtr;
  row += ((yCoord-(height/2))*windowWidth*4);
  for(int y = 0; y < height; y++)
  {
    uint32_t* pixel = (uint32_t*)row;
    pixel += (xCoord-(width/2));
    for(int x = 0; x < width; x++)
    {
      if(pixel >= (uint32_t*)videoMemPtr && pixel <= (uint32_t*)videoMemPtr + ((windowWidth * windowHeight) * 4))
      {
        *pixel++ = color;
      }
    }
    row += windowWidth * 4;
  }
}
