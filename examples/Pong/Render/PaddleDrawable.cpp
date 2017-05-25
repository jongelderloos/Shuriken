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
  int yStart = yCoord - (height/2);

  if(yStart < 0)
  {
    height = height + yStart;
    yStart = 0;
  }

  row += yStart*windowWidth*4;
  for(int y = 0; y < height; y++)
  {
    if((yStart + y < windowHeight) && (yStart + y >= 0))
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
    else if(yStart + y >= windowHeight)
    {
      break;
    }
  }
}
