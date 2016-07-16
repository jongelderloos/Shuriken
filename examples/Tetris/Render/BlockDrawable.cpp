#include "BlockDrawable.h"
#include <stdint.h>

BlockDrawable::BlockDrawable()
{
  type = BLOCK_NONE;
  xCoord = 0;
  yCoord = 0;
}

BlockDrawable::BlockDrawable(BLOCK_TYPE type, int x, int y)
{
  this->type = type;
  xCoord = x;
  yCoord = y;
}

void BlockDrawable::Render(void* videoMemPtr, int windowWidth, int windowHeight)
{
  uint32_t value = 0x0;

  switch(type)
  {
  case BLOCK_STRAIGHT:
    value = 0x2EFEF7;
    break;
  case BLOCK_SQUARE:
    value = 0xFFFF00;
    break;
  case BLOCK_Z:
    value = 0xFF0000;
    break;
  case BLOCK_Z_R:
    value = 0x00FF00;
    break;
  case BLOCK_L:
    value = 0xFF8000;
    break;
  case BLOCK_L_R:
    value = 0x0000FF;
    break;
  case BLOCK_T:
    value = 0x8000FF;
    break;
  case BLOCK_BORDER:
    value = 0xA4A4A4A4;
    break;
  default:
    break;
  }

  uint8_t* row = (uint8_t*)videoMemPtr;
  row += ((yCoord)*windowWidth*25*4);
  for(int y = 0; y < 25; y++)
  {
    uint32_t* pixel = (uint32_t*)row;
    pixel += (xCoord)*25;
    for(int x = 0; x < 25; x++)
    {
      *pixel++ = value;
    }
    row += windowWidth * 4;
  }
}
