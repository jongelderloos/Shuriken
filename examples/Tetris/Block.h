#ifndef BLOCK_H_
#define BLOCK_H_

#define NUM_BLOCK_TYPES     8

typedef enum
{
  BLOCK_NONE,
  BLOCK_STRAIGHT,
  BLOCK_SQUARE,
  BLOCK_Z,
  BLOCK_Z_R,
  BLOCK_L,
  BLOCK_L_R,
  BLOCK_T
} BLOCK_TYPE;

typedef enum
{
  STATE_0 = 0,
  STATE_1 = 2,
  STATE_2 = 4,
  STATE_3 = 6,
} STATE_TYPE;

class Block 
{

public:
  Block();
  Block( BLOCK_TYPE );
  Block operator=(const Block&);
  BLOCK_TYPE getBlockType(void) const;
  void setBlockType(BLOCK_TYPE);
  bool isEvaluated(void) const;
  void setEvaluated(bool);
private:
  BLOCK_TYPE type;
  bool evaluated;

};

#endif // BLOCK_H_
