#include "TextDrawable.h"
#include <cstring>

TextDrawable::TextDrawable()
{
  xCoord = 0;
  yCoord = 0;
}

TextDrawable::TextDrawable(char* text, double x, double y, bool fillBackground)
{
  memcpy(this->text, text, 100);
  xCoord = x;
  yCoord = y;
  this->fillBackground = fillBackground;
  color = 0xFFFFFF;
  size = 1;
}

//TODO: use pixelsPerUnit to scale when the screen size changes?
void TextDrawable::Render(void* videoMemPtr, int windowWidth, int windowHeight, int pixelsPerUnit)
{
  int xPixel = (int)(xCoord * (double)pixelsPerUnit);
  int yPixel = (int)(yCoord * (double)pixelsPerUnit);

  char* currentChar = text;
  uint8_t charMatrix[7][6];

  int charIndx = 0;
  while(*currentChar != 0)
  {
    switch(*currentChar)
    {
    case ' ':
      memcpy(charMatrix, LETTER__, 7*6);
      break;
    case 'A':
      memcpy(charMatrix, LETTER_A, 7*6);
      break;
    case 'B':
      memcpy(charMatrix, LETTER_B, 7*6);
      break;
    case 'C':
      memcpy(charMatrix, LETTER_C, 7*6);
      break;
    case 'D':
      memcpy(charMatrix, LETTER_D, 7*6);
      break;
    case 'E':
      memcpy(charMatrix, LETTER_E, 7*6);
      break;
    case 'F':
      memcpy(charMatrix, LETTER_F, 7*6);
      break;
    case 'G':
      memcpy(charMatrix, LETTER_G, 7*6);
      break;
    case 'H':
      memcpy(charMatrix, LETTER_H, 7*6);
      break;
    case 'I':
      memcpy(charMatrix, LETTER_I, 7*6);
      break;
    case 'J':
      memcpy(charMatrix, LETTER_J, 7*6);
      break;
    case 'K':
      memcpy(charMatrix, LETTER_K, 7*6);
      break;
    case 'L':
      memcpy(charMatrix, LETTER_L, 7*6);
      break;
    case 'M':
      memcpy(charMatrix, LETTER_M, 7*6);
      break;
    case 'N':
      memcpy(charMatrix, LETTER_N, 7*6);
      break;
    case 'O':
      memcpy(charMatrix, LETTER_O, 7*6);
      break;
    case 'P':
      memcpy(charMatrix, LETTER_P, 7*6);
      break;
    case 'Q':
      memcpy(charMatrix, LETTER_Q, 7*6);
      break;
    case 'R':
      memcpy(charMatrix, LETTER_R, 7*6);
      break;
    case 'S':
      memcpy(charMatrix, LETTER_S, 7*6);
      break;
    case 'T':
      memcpy(charMatrix, LETTER_T, 7*6);
      break;
    case 'U':
      memcpy(charMatrix, LETTER_U, 7*6);
      break;
    case 'V':
      memcpy(charMatrix, LETTER_V, 7*6);
      break;
    case 'W':
      memcpy(charMatrix, LETTER_W, 7*6);
      break;
    case 'X':
      memcpy(charMatrix, LETTER_X, 7*6);
      break;
    case 'Y':
      memcpy(charMatrix, LETTER_Y, 7*6);
      break;
    case 'Z':
      memcpy(charMatrix, LETTER_Z, 7*6);
      break;
    case ':':
      memcpy(charMatrix, LETTER_COLON, 7*6);
      break;
    case '!':
      memcpy(charMatrix, LETTER_BANG, 7*6);
      break;
    case '1':
      memcpy(charMatrix, NUMBER_1, 7*6);
      break;
    case '2':
      memcpy(charMatrix, NUMBER_2, 7*6);
      break;
    case '3':
      memcpy(charMatrix, NUMBER_3, 7*6);
      break;
    case '4':
      memcpy(charMatrix, NUMBER_4, 7*6);
      break;
    case '5':
      memcpy(charMatrix, NUMBER_5, 7*6);
      break;
    case '6':
      memcpy(charMatrix, NUMBER_6, 7*6);
      break;
    case '7':
      memcpy(charMatrix, NUMBER_7, 7*6);
      break;
    case '8':
      memcpy(charMatrix, NUMBER_8, 7*6);
      break;
    case '9':
      memcpy(charMatrix, NUMBER_9, 7*6);
      break;
    case '0':
      memcpy(charMatrix, NUMBER_0, 7*6);
      break;
    default:
      break;
    }
    
    uint8_t* row = (uint8_t*)videoMemPtr;
    row += ((yPixel)*windowWidth*4);
    for(int y = 0; y < 7 * size; y++)
    {
      uint32_t* pixel = (uint32_t*)row;
      pixel += xPixel + (6 * size * charIndx);
      for(int x = 0; x < 6 * size; x++)
      {
        if(charMatrix[6-(y/size)][x/size] == 1)
        {
          *pixel++ = color;
        }
        else
        {
          if(fillBackground)
          {
            *pixel++ = 0x0;
          }
          else
          {
            pixel++;
          }
        }
      }
      row += windowWidth * 4;
    }

    charIndx++;
    currentChar++;
  }
}

void TextDrawable::SetColor(uint32_t color)
{
  this->color = color;
}

void TextDrawable::SetSize(int size)
{
  this->size = size;
}

