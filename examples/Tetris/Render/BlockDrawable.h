#ifndef BLOCKDRAWABLE_H_
#define BLOCKDRAWABLE_H_

#include "Drawable2D.h"
#include "Block.h"

class BlockDrawable : public Drawable2D
{
public:
  BlockDrawable();
  BlockDrawable(BLOCK_TYPE, int, int);
  void Render(void*, int);
  BLOCK_TYPE type;
  int xCoord;
  int yCoord;

private:
};

#endif //BLOCKDRAWABLE_H_
