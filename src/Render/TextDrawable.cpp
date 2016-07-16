#include "TextDrawable.h"
#include <cstring>

TextDrawable::TextDrawable()
{
  xPercent = 0;
  yPercent = 0;
}

TextDrawable::TextDrawable(char* text, double x, double y, bool fillBackground)
{
  memcpy(this->text, text, 100);
  xPercent = x;
  yPercent = y;
  this->fillBackground = fillBackground;
}

void TextDrawable::Render(void* videoMemPtr, int windowWidth, int windowHeight)
{
  int xPixel = (int)((xPercent / (double)100) * (double)windowWidth);
  int yPixel = (int)((yPercent / (double)100) * (double)windowHeight);

  uint32_t value = 0xFFFFFF;

  char* currentChar = text;
  uint8_t charMatrix[7][5];

  int charIndx = 0;
  while(*currentChar != 0)
  {
    switch(*currentChar)
    {
    case ' ':
      memcpy(charMatrix, LETTER__, 7*5);
      break;
    case 'A':
      memcpy(charMatrix, LETTER_A, 7*5);
      break;
    case 'B':
      memcpy(charMatrix, LETTER_B, 7*5);
      break;
    case 'C':
      memcpy(charMatrix, LETTER_C, 7*5);
      break;
    case 'D':
      memcpy(charMatrix, LETTER_D, 7*5);
      break;
    case 'E':
      memcpy(charMatrix, LETTER_E, 7*5);
      break;
    case 'F':
      memcpy(charMatrix, LETTER_F, 7*5);
      break;
    case 'G':
      memcpy(charMatrix, LETTER_G, 7*5);
      break;
    case 'H':
      memcpy(charMatrix, LETTER_H, 7*5);
      break;
    case 'I':
      memcpy(charMatrix, LETTER_I, 7*5);
      break;
    case 'J':
      memcpy(charMatrix, LETTER_J, 7*5);
      break;
    case 'K':
      memcpy(charMatrix, LETTER_K, 7*5);
      break;
    case 'L':
      memcpy(charMatrix, LETTER_L, 7*5);
      break;
    case 'M':
      memcpy(charMatrix, LETTER_M, 7*5);
      break;
    case 'N':
      memcpy(charMatrix, LETTER_N, 7*5);
      break;
    case 'O':
      memcpy(charMatrix, LETTER_O, 7*5);
      break;
    case 'P':
      memcpy(charMatrix, LETTER_P, 7*5);
      break;
    case 'Q':
      memcpy(charMatrix, LETTER_Q, 7*5);
      break;
    case 'R':
      memcpy(charMatrix, LETTER_R, 7*5);
      break;
    case 'S':
      memcpy(charMatrix, LETTER_S, 7*5);
      break;
    case 'T':
      memcpy(charMatrix, LETTER_T, 7*5);
      break;
    case 'U':
      memcpy(charMatrix, LETTER_U, 7*5);
      break;
    case 'V':
      memcpy(charMatrix, LETTER_V, 7*5);
      break;
    case 'W':
      memcpy(charMatrix, LETTER_W, 7*5);
      break;
    case 'X':
      memcpy(charMatrix, LETTER_X, 7*5);
      break;
    case 'Y':
      memcpy(charMatrix, LETTER_Y, 7*5);
      break;
    case 'Z':
      memcpy(charMatrix, LETTER_Z, 7*5);
      break;
    case ':':
      memcpy(charMatrix, LETTER_COLON, 7*5);
      break;
    case '!':
      memcpy(charMatrix, LETTER_BANG, 7*5);
      break;
    case '1':
      memcpy(charMatrix, NUMBER_1, 7*5);
      break;
    case '2':
      memcpy(charMatrix, NUMBER_2, 7*5);
      break;
    case '3':
      memcpy(charMatrix, NUMBER_3, 7*5);
      break;
    case '4':
      memcpy(charMatrix, NUMBER_4, 7*5);
      break;
    case '5':
      memcpy(charMatrix, NUMBER_5, 7*5);
      break;
    case '6':
      memcpy(charMatrix, NUMBER_6, 7*5);
      break;
    case '7':
      memcpy(charMatrix, NUMBER_7, 7*5);
      break;
    case '8':
      memcpy(charMatrix, NUMBER_8, 7*5);
      break;
    case '9':
      memcpy(charMatrix, NUMBER_9, 7*5);
      break;
    case '0':
      memcpy(charMatrix, NUMBER_0, 7*5);
      break;
    default:
      break;
    }
    
    uint8_t* row = (uint8_t*)videoMemPtr;
    row += ((yPixel)*windowWidth*4);
    for(int y = 0; y < 7; y++)
    {
      uint32_t* pixel = (uint32_t*)row;
      pixel += xPixel + (6 * charIndx);
      for(int x = 0; x < 5; x++)
      {
        if(charMatrix[6-y][x] == 1)
        {
          *pixel++ = value;
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
