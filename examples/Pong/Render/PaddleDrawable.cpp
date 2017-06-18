#include "PaddleDrawable.h"
#include <stdint.h>

PaddleDrawable::PaddleDrawable()
{
  xCoord = 0;
  yCoord = 0;
}

PaddleDrawable::PaddleDrawable(float x, float y, float width, float height)
{
  xCoord = x;
  yCoord = y;
  this->width = width;
  this->height = height;
}

void PaddleDrawable::Render(void* videoMemPtr, int windowWidth, int windowHeight, int pixelsPerUnit)
{
  int xPixels = xCoord * pixelsPerUnit;
  int yPixels = yCoord * pixelsPerUnit;
  int widthPixels = width * pixelsPerUnit;
  int heightPixels = height * pixelsPerUnit;

  uint8_t* row = (uint8_t*)videoMemPtr;
  int yStart = yPixels - (heightPixels/2);

  if(yStart < 0)
  {
    heightPixels = heightPixels + yStart;
    yStart = 0;
  }

  row += yStart*windowWidth*4;
  for(int y = 0; y < heightPixels; y++)
  {
    if((yStart + y < windowHeight) && (yStart + y >= 0))
    {
      uint32_t* pixel = (uint32_t*)row;
      pixel += (xPixels-(widthPixels/2));
      for(int x = 0; x < widthPixels; x++)
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
