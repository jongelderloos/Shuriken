#include "Board.h"
#include "stdio.h"
#include "Windows.h"
#include "BlockDrawable.h"


const int blocks_loc[][8] = {{ 0, 0,  0, 0,  0, 0,  0, 0  },   // BLOCK_NONE
                             { 0, 0,  0, 0,  0, 0,  0, 0  },   // BLOCK_BORDER
                             { 3, 19, 3, 18, 3, 17, 3, 16 },   // BLOCK_STRAIGHT
                             { 3, 18, 4, 18, 3, 17, 4, 17 },   // BLOCK_SQUARE
                             { 4, 18, 3, 17, 4, 17, 3, 16 },   // BLOCK_Z
                             { 3, 18, 3, 17, 4, 17, 4, 16 },   // BLOCK_Z_R
                             { 3, 18, 4, 18, 4, 17, 4, 16 },   // BLOCK_L
                             { 4, 18, 4, 17, 3, 16, 4, 16 },   // BLOCK_L_R
                             { 4, 18, 3, 17, 4, 17, 4, 16 }};  // BLOCK_T

// Rotate arrays for straight block
const int straight_first_values[] = { 2, -1, -1, -2, -2, 1, 1, 2 };
const int straight_second_values[] = { 1, 0, 0, -1, -1, 0, 0, 1 };
const int straight_third_values[] = { 0, 1, 1, 0, 0, -1, -1, 0 };
const int straight_fourth_values[] = { -1, 2, 2, 1, 1, -2, -2, -1 };
// Rotate arrays for Z block
const int z_first_values[] = { 1, -1, -1, -1, -1, 1, 1, 1 };
const int z_second_values[] = { 1, 1, 1, -1, -1, -1, -1, 1 };
const int z_third_values[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const int z_fourth_values[] = { 0, 2, 2, 0, 0, -2, -2, 0 };
// Rotate arrays for Z_R block
const int z_r_first_values[] = { 2, 0, 0, -2, -2, 0, 0, 2 };
const int z_r_second_values[] = { 1, 1, 1, -1, -1, -1, -1, 1 };
const int z_r_third_values[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const int z_r_fourth_values[] = { -1, 1, 1, 1, 1, -1, -1, -1};
// Rotate arrays for L block
const int l_first_values[] = { 2, 0, 0, -2, -2, 0, 0, 2 };
const int l_second_values[] = { 1, -1, -1, -1, -1, 1, 1, 1 };
const int l_third_values[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const int l_fourth_values[] = { -1, 1, 1, 1, 1, -1, -1, -1};
// Rotate arrays for L_R block
const int l_r_first_values[] = { 1, -1, -1, -1, -1, 1, 1, 1 };
const int l_r_second_values[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const int l_r_third_values[] = { 0, 2, 2, 0, 0, -2, -2, 0 };
const int l_r_fourth_values[] = { -1, 1, 1, 1, 1, -1, -1, -1 };
// Rotate arrays for T block
const int t_first_values[] = { 1, -1, -1, -1, -1, 1, 1, 1 };
const int t_second_values[] = { 1, 1, 1, -1, -1, -1, -1, 1 };
const int t_third_values[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const int t_fourth_values[] = { -1, 1, 1, 1, 1, -1, -1, -1 };

int score = 0;
int rowsMade = 0;
int totalRowsMade = 0;
int modifier = 1; 
int bonus = 1;
HANDLE output;
COORD pos;
struct Falling gameFalling;
const int modifierGap = 5;


// TODO variable board size
Board::Board()
{
  width = MAX_WIDTH;
  height = MAX_HEIGHT;
  msProcessTime = 250;
  initializeBoard();
  gameState = GAME_RUNNING;
}

Board::~Board()
{
  clearBoard();
}

void Board::initializeBoard(void)
{
  OutputDebugStringA("Initializing board");
  for(int i = 0; i < height; i++)
  {
    std::vector<Block*> curRow;
    for(int j = 0; j < width; j++)
    {
      curRow.push_back( new Block(BLOCK_NONE) );
      BlockDrawable *curBlock = new BlockDrawable(BLOCK_NONE, j + 1, i + 1);
      curBlock->id = j + (i * width);
      render.addToForeground(curBlock);
    }
    board.push_back(curRow);
    rowState.push_back(STATE_NORMAL);
  }
  
  fall.active = false;
  for(int i = 0; i < 8; i++)
  {
    fall.coords[i] = 0;
  }

  // Create blocks for background
  for(int y = 0; y < 22; y++)
  {
    for(int x = 0; x < 15; x++)
    {
      if(((x == 0) || (x == 9) || (x == 14) || (y == 0) || (y == 21)) ||
        (((x >= 10) && (x < 14)) && (y == 16)))
      {
        BlockDrawable *curBlock = new BlockDrawable(BLOCK_BORDER, x, y);
        curBlock->id = 3000 + x + (y * height);
        render.addToBackground(curBlock);
      }
    }
  }

  // Create blocks for the on deck area background
  for(int i = 17; i < 21; i++)
  {
    for(int j = 10; j < 14; j++)
    {
      BlockDrawable *curBlock = new BlockDrawable(BLOCK_NONE, j, i);
      curBlock->id = 2000 + j + (i * 4);
      render.addToBackground(curBlock);
    }
  }

  // Create 4 place holder blocks for the on deck blocks
  for(int i = 0; i < 4; i++)
  {
    BlockDrawable *curBlock = new BlockDrawable(BLOCK_NONE, blocks_loc[0][2 * i] + 8, blocks_loc[0][(2 * i) + 1] + 1);
    curBlock->id = 1001 + i;
    render.addToForeground(curBlock);
  }
}

void Board::clearBoard(void)
{
  OutputDebugStringA("Clearing board");
  for(auto row: board)
  {
    for(auto block: row)
    {
      delete block;
      block = NULL;
    }
  }

  for(auto &row: rowState)
  {
    row = STATE_NONE;
  }
}

Block* Board::getBlock(int col, int row)
{
  return board[row][col];
}

ROW_STATE Board::getRowState(int r)
{
  return rowState[r];
}

ROW_STATE Board::getRowState(std::vector<Block*> row)
{
  ROW_STATE state = static_cast<ROW_STATE>(-1);
  for(int idx = 0; idx < height; idx++)
  {
    if(board[idx] == row)
    {
      state = getRowState(idx);
      break;
    }
  }
  return state;
}

int Board::getRowsMade(void)
{
  int numRows = 0;

  for(auto state: rowState)
  {
    if(state == STATE_FLASH)
    {
      numRows++;
    }
  }
  return numRows;
}

void Board::evalBoard(void)
{
  bool blockFalling;
  bool deletion = false;
  // Loop through each row and evaluate if it is full
  for(int row = 0; row < height; row++)
  {   
    if(deletion == true)
    {
      break;
    }

    switch(getRowState(row))
    {
    // if a row is deleted, set to normal..
    case STATE_DELETE:
      rowState[row] = STATE_NONE;
      
      // Loop back up and set any rows with blocks to falling
      for(int row2 = row+1; row2 < height; row2++)
      {
        for(int col2 = 0; col2 < width; col2++)
        {
          if(getRowState(row2) != STATE_DELETE)
          {
            if(board[row2][col2]->getBlockType() != BLOCK_NONE)
            {
              rowState[row2] = STATE_FALLING;
              break;
            }
            else
            {
              rowState[row2] = STATE_NONE;
            }
          }
          else
          {
            rowState[row2] = STATE_DELETE;
          }
        }
        // if the row didnt have any blocks set to normal and stop looking
        if(rowState[row2] == STATE_NONE)
        {
          break;
        }
      }
      deletion = true;
      break;
  
    case STATE_FLASH:
      rowState[row] = STATE_DELETE;
      break;

    case STATE_FALLING:
      if((row == 0) || (getRowState(row-1) == STATE_NORMAL))
      {
        rowState[row] = STATE_NORMAL;
      }         
      break;
      
    case STATE_NORMAL:
      for(int column = 0; column < width; column++)
      {
        blockFalling = false;
        // Check to see if any blocks are part of the falling block, so it does not cause a
        //  row to flash while a block is falling through it
        for(int i = 0; i < 8; i+=2)
        {
          if((fall.coords[i] == column) && (fall.coords[i+1] == row))
          {
            blockFalling = true;
          }
        }
        if(blockFalling == true)
        {
          rowState[row] = STATE_NORMAL;
          break;
        }
        else
        {
          // if any space in the row is empty the row is in the normal state
          if(board[row][column]->getBlockType() == BLOCK_NONE)
          {
            rowState[row] = STATE_NORMAL;
            break;
          }
          else
          {
            rowState[row] = STATE_FLASH;
          }
        }
      }
      break;

    default:
      break;
    }
  } 
}

void Board::processBoard(void)
{
  bool stopFalling = false;
  int x,y = 0;
  bool skip = false;
  
  for(int row = 0; row < height; row++)
  {
    if(this->getRowState(row) == STATE_DELETE)
    {
      for(int col = 0; col < width; col++)
      {
        board[row][col]->setBlockType(BLOCK_NONE);
        board[row][col]->setEvaluated(false);
      }
    }
    
    if(this->getRowState(row) == STATE_FALLING)
    {
      // Move the falling blocks down a row
      for(int col = 0; col < width; col++)
      {
        board[row-1][col]->setBlockType(board[row][col]->getBlockType());
        board[row-1][col]->setEvaluated(false);
        
        board[row][col]->setBlockType(BLOCK_NONE);
        board[row][col]->setEvaluated(false);
      }

      // Adjust the row state
      rowState[row-1] = STATE_FALLING;
      rowState[row] = STATE_NONE;
    }
  }
  
  if(fall.active == true)
  {
    for(int i = 0; i < 8; i+=2)
    {
      x = fall.coords[i];
      y = fall.coords[i+1];
      
      if(stopFalling == true)
      {
        fall.coords[i] = 0;
        fall.coords[i+1] = 0;
      }
      else
      {
        // not on the bottom row
        if(y > 0)
        {
          skip = false;
          
          for(int j = 0; j < 8; j+=2)
          {
            if((x == fall.coords[j]) && (y-1 == fall.coords[j+1]))
            {
              // this is part of the block
              skip = true;
              break;
            }
          }
          
          if(skip == false)
          {
            if(board[y-1][x]->getBlockType() != BLOCK_NONE)
            {
              // Set to be not falling
              stopFalling = true;
              
              fall.active = false;
              fall.coords[i] = 0;
              fall.coords[i+1] = 0;
            }
          }
          
        }
        else
        {
          stopFalling = true;
            
          fall.active = false;
          fall.coords[i] = 0;
          fall.coords[i+1] = 0;
        }
      }
    }
  }
  
  // process the fall if we didnt detect any hits
  if(fall.active == true)
  {
    BLOCK_TYPE curType;
  
    // delete old position
    for(int i = 0; i < 8; i+=2)
    {  
      x = fall.coords[i];
      y = fall.coords[i+1];
      
      curType = board[y][x]->getBlockType();
      
      board[y][x]->setBlockType(BLOCK_NONE);
      board[y][x]->setEvaluated(false);
    }
    
    
    // add at new position
    for(int i = 0; i < 8; i+=2)
    {  
      x = fall.coords[i];
      y = fall.coords[i+1];
      fall.coords[i+1]--;
      
      board[y-1][x]->setBlockType(curType);
      board[y-1][x]->setEvaluated(false);
    }
  }
}

void Board::addBlock(void)
{
  Block newBlock;
  BLOCK_TYPE type;
  
  type = blockOnDeck.getBlockType();
  blockOnDeck = newBlock;

  BLOCK_TYPE onDeckType = blockOnDeck.getBlockType();
  for(int i = 0; i < 4; i++)
  {
    BlockDrawable *curBlock = new BlockDrawable(onDeckType, blocks_loc[onDeckType][2 * i] + 8, blocks_loc[onDeckType][(2 * i) + 1] + 1);
    curBlock->id = 1001 + i;
    render.updateForeground(curBlock);
  }
  
  // If there is space on the board where this block is going
  if(board[blocks_loc[type][1]][blocks_loc[type][0]]->getBlockType() == BLOCK_NONE &&
     board[blocks_loc[type][3]][blocks_loc[type][2]]->getBlockType() == BLOCK_NONE &&
     board[blocks_loc[type][5]][blocks_loc[type][4]]->getBlockType() == BLOCK_NONE &&
     board[blocks_loc[type][7]][blocks_loc[type][6]]->getBlockType() == BLOCK_NONE)
  {
    // Setup the fall coords with the new locations
    fall.coords[0] = blocks_loc[type][0];
    fall.coords[1] = blocks_loc[type][1];
    fall.coords[2] = blocks_loc[type][2];
    fall.coords[3] = blocks_loc[type][3];
    fall.coords[4] = blocks_loc[type][4];
    fall.coords[5] = blocks_loc[type][5];
    fall.coords[6] = blocks_loc[type][6];
    fall.coords[7] = blocks_loc[type][7];
    
    // Add the block to the board
    board[blocks_loc[type][1]][blocks_loc[type][0]]->setBlockType(type);
    board[blocks_loc[type][3]][blocks_loc[type][2]]->setBlockType(type);
    board[blocks_loc[type][5]][blocks_loc[type][4]]->setBlockType(type);
    board[blocks_loc[type][7]][blocks_loc[type][6]]->setBlockType(type);

    fall.active = true;
    fall.type = type;
    fall.state = STATE_0;
  }
  else
  {
    gameState = GAME_END;
  }
}

// TODO just processing the board is maybe not the most effecient way to do this,
// possibly factor out the needed logic and call only it here
void Board::drop(void)
{
  while(fall.active == true)
  {
    this->evalBoard();
    this->processBoard();
  }
}

void Board::moveBlock(MOVE_DIR direction)
{
  const int LEFT_WALL = 0;
  const int RIGHT_WALL = 7;
  bool isBlocked = false;
  int x,y = 0;
  bool skip = false;
  int offset = 0;

  // Set our offset based on the direction
  if(direction == MOVE_LEFT)
  {
    offset = -1;
  }
  else if(direction == MOVE_RIGHT)
  {
    offset = 1;
  }


  if(fall.active == true)
  {
    for(int i = 0; i < 8; i+=2)
    {
      x = fall.coords[i];
      y = fall.coords[i+1];
      
      // if not trying to move into the wall
      if( ((x > LEFT_WALL) && (direction == MOVE_LEFT)) || ((x < RIGHT_WALL) && (direction == MOVE_RIGHT)) )
      {
        skip = false;
        
        for(int j = 0; j < 8; j+=2)
        {
          if((x+offset == fall.coords[j]) && (y == fall.coords[j+1]))
          {
            // this is part of the block
            skip = true;
            break;
          }
        }
        if(skip == false)
        {
          if(board[y][x+offset]->getBlockType() != BLOCK_NONE)
          {
            isBlocked = true;
            break;
          }
        }
      }
      else
      {
        isBlocked = true;
        break;
      }
    }
  }
  
  // process the move if we didnt detect any hits
  if(isBlocked == false)
  {
    BLOCK_TYPE curType;
  
    // delete old position
    for(int i = 0; i < 8; i+=2)
    {  
      x = fall.coords[i];
      y = fall.coords[i+1];

      curType = board[y][x]->getBlockType();

      board[y][x]->setBlockType(BLOCK_NONE);
      board[y][x]->setEvaluated(false);
    }
    
    // add at new position
    for(int i = 0; i < 8; i+=2)
    {  
      x = fall.coords[i];
      y = fall.coords[i+1];      
      fall.coords[i] += offset;
      
      board[y][x+offset]->setBlockType(curType);
      board[y][x+offset]->setEvaluated(false);
    }
  }
}

// TODO merge with counterClock version
void Board::rotateClock(void)
{
  bool isBlocked = false;
  bool skip = false;
  int newCoords[8];
  

  if(fall.active == true)
  {
    // Calculate the rotation based off a pre set array since there is a small number
    // of possible rotations possible
    switch(fall.type)
    {
      case BLOCK_STRAIGHT:
        newCoords[0] = fall.coords[0] + straight_first_values[fall.state];
        newCoords[1] = fall.coords[1] + straight_first_values[fall.state+1];
        newCoords[2] = fall.coords[2] + straight_second_values[fall.state];
        newCoords[3] = fall.coords[3] + straight_second_values[fall.state+1];
        newCoords[4] = fall.coords[4] + straight_third_values[fall.state];
        newCoords[5] = fall.coords[5] + straight_third_values[fall.state+1];
        newCoords[6] = fall.coords[6] + straight_fourth_values[fall.state];
        newCoords[7] = fall.coords[7] + straight_fourth_values[fall.state+1];
        break;
      case BLOCK_SQUARE:
        newCoords[0] = fall.coords[0];
        newCoords[1] = fall.coords[1];
        newCoords[2] = fall.coords[2];
        newCoords[3] = fall.coords[3];
        newCoords[4] = fall.coords[4];
        newCoords[5] = fall.coords[5];
        newCoords[6] = fall.coords[6];
        newCoords[7] = fall.coords[7];
        break;
      case BLOCK_Z:
        newCoords[0] = fall.coords[0] + z_first_values[fall.state];
        newCoords[1] = fall.coords[1] + z_first_values[fall.state+1];
        newCoords[2] = fall.coords[2] + z_second_values[fall.state];
        newCoords[3] = fall.coords[3] + z_second_values[fall.state+1];
        newCoords[4] = fall.coords[4] + z_third_values[fall.state];
        newCoords[5] = fall.coords[5] + z_third_values[fall.state+1];
        newCoords[6] = fall.coords[6] + z_fourth_values[fall.state];
        newCoords[7] = fall.coords[7] + z_fourth_values[fall.state+1];
        break;
      case BLOCK_Z_R:
        newCoords[0] = fall.coords[0] + z_r_first_values[fall.state];
        newCoords[1] = fall.coords[1] + z_r_first_values[fall.state+1];
        newCoords[2] = fall.coords[2] + z_r_second_values[fall.state];
        newCoords[3] = fall.coords[3] + z_r_second_values[fall.state+1];
        newCoords[4] = fall.coords[4] + z_r_third_values[fall.state];
        newCoords[5] = fall.coords[5] + z_r_third_values[fall.state+1];
        newCoords[6] = fall.coords[6] + z_r_fourth_values[fall.state];
        newCoords[7] = fall.coords[7] + z_r_fourth_values[fall.state+1];
        break;
      case BLOCK_L:
        newCoords[0] = fall.coords[0] + l_first_values[fall.state];
        newCoords[1] = fall.coords[1] + l_first_values[fall.state+1];
        newCoords[2] = fall.coords[2] + l_second_values[fall.state];
        newCoords[3] = fall.coords[3] + l_second_values[fall.state+1];
        newCoords[4] = fall.coords[4] + l_third_values[fall.state];
        newCoords[5] = fall.coords[5] + l_third_values[fall.state+1];
        newCoords[6] = fall.coords[6] + l_fourth_values[fall.state];
        newCoords[7] = fall.coords[7] + l_fourth_values[fall.state+1];
        break;
      case BLOCK_L_R:
        newCoords[0] = fall.coords[0] + l_r_first_values[fall.state];
        newCoords[1] = fall.coords[1] + l_r_first_values[fall.state+1];
        newCoords[2] = fall.coords[2] + l_r_second_values[fall.state];
        newCoords[3] = fall.coords[3] + l_r_second_values[fall.state+1];
        newCoords[4] = fall.coords[4] + l_r_third_values[fall.state];
        newCoords[5] = fall.coords[5] + l_r_third_values[fall.state+1];
        newCoords[6] = fall.coords[6] + l_r_fourth_values[fall.state];
        newCoords[7] = fall.coords[7] + l_r_fourth_values[fall.state+1];
        break;
      case BLOCK_T:
        newCoords[0] = fall.coords[0] + t_first_values[fall.state];
        newCoords[1] = fall.coords[1] + t_first_values[fall.state+1];
        newCoords[2] = fall.coords[2] + t_second_values[fall.state];
        newCoords[3] = fall.coords[3] + t_second_values[fall.state+1];
        newCoords[4] = fall.coords[4] + t_third_values[fall.state];
        newCoords[5] = fall.coords[5] + t_third_values[fall.state+1];
        newCoords[6] = fall.coords[6] + t_fourth_values[fall.state];
        newCoords[7] = fall.coords[7] + t_fourth_values[fall.state+1];
        break;

      default:
        break;
    }
    
    // Check if the new rotation will hit anything
    for(int i = 0; i < 8; i+=2)
    {
      // check out of bounds areas
      if((newCoords[i] > 7) ||
          (newCoords[i] < 0) ||
          (newCoords[i+1] < 0))
      {
        isBlocked = true;
      }
      else
      {
        // check for other blocks
        if(board[newCoords[i+1]][newCoords[i]]->getBlockType() != BLOCK_NONE)
        {
          skip = false;
          for(int j = 0; j < 8; j+=2)
          {
            if((newCoords[i] == fall.coords[j]) && (newCoords[i+1] == fall.coords[j+1]))
            {
              skip = true;
              break;
            }
          }
          if(skip == false)
          {
            isBlocked = true;
            break;
          }
        }
      }
    }

    // Update the board if the rotation is not blocked by anything
    if(isBlocked == false)
    {
      int x,y;
      // Remove pre-rotated blocks
      for(int i = 0; i < 8; i+=2)
      {
        x = fall.coords[i];
        y = fall.coords[i+1];
        
        board[y][x]->setBlockType(BLOCK_NONE);
        board[y][x]->setEvaluated(false);
      }
      
      // Update fall coords to the new rotated position
      for(int i = 0; i < 8; i+=2)
      {
        x = fall.coords[i] = newCoords[i];
        y = fall.coords[i+1] = newCoords[i+1];
        
        board[y][x]->setBlockType(fall.type);
        board[y][x]->setEvaluated(false);
      }
      
      // Update the falling blocks rotation position/state
      int state = (int)fall.state;
      fall.state = STATE_TYPE((state+=2)%8);
    }
  }
}

void Board::rotateCounterClock(void)
{
  bool isBlocked = false;
  bool skip = false;
  int newCoords[8];
  

  if(fall.active == true)
  {
    // Calculate the rotation based off a pre set array since there is a small number
    // of possible rotations possible
    switch(fall.type)
    {
      case BLOCK_STRAIGHT:
        newCoords[0] = fall.coords[0] - straight_first_values[(fall.state+6)%8];
        newCoords[1] = fall.coords[1] - straight_first_values[(fall.state+7)%8];
        newCoords[2] = fall.coords[2] - straight_second_values[(fall.state+6)%8];
        newCoords[3] = fall.coords[3] - straight_second_values[(fall.state+7)%8];
        newCoords[4] = fall.coords[4] - straight_third_values[(fall.state+6)%8];
        newCoords[5] = fall.coords[5] - straight_third_values[(fall.state+7)%8];
        newCoords[6] = fall.coords[6] - straight_fourth_values[(fall.state+6)%8];
        newCoords[7] = fall.coords[7] - straight_fourth_values[(fall.state+7)%8];
        break;
      case BLOCK_SQUARE:
        newCoords[0] = fall.coords[0];
        newCoords[1] = fall.coords[1];
        newCoords[2] = fall.coords[2];
        newCoords[3] = fall.coords[3];
        newCoords[4] = fall.coords[4];
        newCoords[5] = fall.coords[5];
        newCoords[6] = fall.coords[6];
        newCoords[7] = fall.coords[7];
        break;
      case BLOCK_Z:
        newCoords[0] = fall.coords[0] - z_first_values[(fall.state+6)%8];
        newCoords[1] = fall.coords[1] - z_first_values[(fall.state+7)%8];
        newCoords[2] = fall.coords[2] - z_second_values[(fall.state+6)%8];
        newCoords[3] = fall.coords[3] - z_second_values[(fall.state+7)%8];
        newCoords[4] = fall.coords[4] - z_third_values[(fall.state+6)%8];
        newCoords[5] = fall.coords[5] - z_third_values[(fall.state+7)%8];
        newCoords[6] = fall.coords[6] - z_fourth_values[(fall.state+6)%8];
        newCoords[7] = fall.coords[7] - z_fourth_values[(fall.state+7)%8];
        break;
      case BLOCK_Z_R:
        newCoords[0] = fall.coords[0] - z_r_first_values[(fall.state+6)%8];
        newCoords[1] = fall.coords[1] - z_r_first_values[(fall.state+7)%8];
        newCoords[2] = fall.coords[2] - z_r_second_values[(fall.state+6)%8];
        newCoords[3] = fall.coords[3] - z_r_second_values[(fall.state+7)%8];
        newCoords[4] = fall.coords[4] - z_r_third_values[(fall.state+6)%8];
        newCoords[5] = fall.coords[5] - z_r_third_values[(fall.state+7)%8];
        newCoords[6] = fall.coords[6] - z_r_fourth_values[(fall.state+6)%8];
        newCoords[7] = fall.coords[7] - z_r_fourth_values[(fall.state+7)%8];
        break;
      case BLOCK_L:
        newCoords[0] = fall.coords[0] - l_first_values[(fall.state+6)%8];
        newCoords[1] = fall.coords[1] - l_first_values[(fall.state+7)%8];
        newCoords[2] = fall.coords[2] - l_second_values[(fall.state+6)%8];
        newCoords[3] = fall.coords[3] - l_second_values[(fall.state+7)%8];
        newCoords[4] = fall.coords[4] - l_third_values[(fall.state+6)%8];
        newCoords[5] = fall.coords[5] - l_third_values[(fall.state+7)%8];
        newCoords[6] = fall.coords[6] - l_fourth_values[(fall.state+6)%8];
        newCoords[7] = fall.coords[7] - l_fourth_values[(fall.state+7)%8];
        break;
      case BLOCK_L_R:
        newCoords[0] = fall.coords[0] - l_r_first_values[(fall.state+6)%8];
        newCoords[1] = fall.coords[1] - l_r_first_values[(fall.state+7)%8];
        newCoords[2] = fall.coords[2] - l_r_second_values[(fall.state+6)%8];
        newCoords[3] = fall.coords[3] - l_r_second_values[(fall.state+7)%8];
        newCoords[4] = fall.coords[4] - l_r_third_values[(fall.state+6)%8];
        newCoords[5] = fall.coords[5] - l_r_third_values[(fall.state+7)%8];
        newCoords[6] = fall.coords[6] - l_r_fourth_values[(fall.state+6)%8];
        newCoords[7] = fall.coords[7] - l_r_fourth_values[(fall.state+7)%8];
        break;
      case BLOCK_T:
        newCoords[0] = fall.coords[0] - t_first_values[(fall.state+6)%8];
        newCoords[1] = fall.coords[1] - t_first_values[(fall.state+7)%8];
        newCoords[2] = fall.coords[2] - t_second_values[(fall.state+6)%8];
        newCoords[3] = fall.coords[3] - t_second_values[(fall.state+7)%8];
        newCoords[4] = fall.coords[4] - t_third_values[(fall.state+6)%8];
        newCoords[5] = fall.coords[5] - t_third_values[(fall.state+7)%8];
        newCoords[6] = fall.coords[6] - t_fourth_values[(fall.state+6)%8];
        newCoords[7] = fall.coords[7] - t_fourth_values[(fall.state+7)%8];
        break;

      default:
        break;
    }
    
    // Check if the new rotation will hit anything
    for(int i = 0; i < 8; i+=2)
    {
      // check out of bounds areas
      if((newCoords[i] > 7) ||
        (newCoords[i] < 0) ||
        (newCoords[i+1] < 0))
      {
        isBlocked = true;
      }
      else
      {
        // check for other blocks
        if(board[newCoords[i+1]][newCoords[i]]->getBlockType() != BLOCK_NONE)
        {
          skip = false;
          for(int j = 0; j < 8; j+=2)
          {
            if((newCoords[i] == fall.coords[j]) && (newCoords[i+1] == fall.coords[j+1]))
            {
              skip = true;
              break;
            }
          }
          if(skip == false)
          {
            isBlocked = true;
            break;
          }
        }
      }
    }

    // Update the board if the rotation is not blocked by anything
    if(isBlocked == false)
    {
      int x,y;
      // Remove pre-rotated blocks
      for(int i = 0; i < 8; i+=2)
      {
        x = fall.coords[i];
        y = fall.coords[i+1];
        
        board[y][x]->setBlockType(BLOCK_NONE);
        board[y][x]->setEvaluated(false);
      }
      
      // Update fall coords to the new rotated position
      for(int i = 0; i < 8; i+=2)
      {
        x = fall.coords[i] = newCoords[i];
        y = fall.coords[i+1] = newCoords[i+1];
        
        board[y][x]->setBlockType(fall.type);
        board[y][x]->setEvaluated(false);
      }
      
      // Update the falling blocks rotation position/state
      int state = (int)fall.state;
      fall.state = STATE_TYPE((state+=6)%8);
    }
  }
}

void Board::removeRows(int r)
{
  for(int i = 0; i < r; i++) 
  {
    for(int j = 0; j < width; j++)
    {
      board[i][j]->setBlockType(BLOCK_NONE);
    }
  }
}

struct Falling Board::getFalling(void)
{
  return fall;
}

void Board::setFalling(struct Falling f)
{
  fall = f;
}

void Board::start(void)
{
  output = GetStdHandle(STD_OUTPUT_HANDLE);
  running = true;
  Block newBlock;
  blockOnDeck = newBlock;
  addBlock();
}

bool Board::isRunning(void)
{
  return running;
}

void Board::handleInput(char key)
{
  switch(key)
  {
  case 0x61:
  case 0x41:
    if(gameState == GAME_RUNNING)
    {
      this->moveBlock(MOVE_LEFT);
    }
    break;
  case 0x64:
  case 0x44:
    if(gameState == GAME_RUNNING)
    {
      this->moveBlock(MOVE_RIGHT);
    }
    break;
  case 0x77:
  case 0x57:
    if(gameState == GAME_RUNNING)
    {
      this->rotateClock();
    }
    break;
  case 0x73:
  case 0x53:
    if(gameState == GAME_RUNNING)
    {
      this->rotateCounterClock();
    }
    break;
  case 0x20:
    if(gameState == GAME_RUNNING)
    {
      this->drop();
    }
    break;
  case 0x70:
  case 0x50:
    if(gameState == GAME_RUNNING)
    {
      gameState = GAME_PAUSE;
    }
    else if(gameState == GAME_PAUSE)
    {
      gameState = GAME_RUNNING;
    }
    break;
  case 0x1B:
    if((gameState == GAME_RUNNING) || (gameState == GAME_END))
    {
      OutputDebugStringA("Ending game");
      gameState = GAME_END;
      running = false;
      //system("CLS");
      // TODO: clear screen
    }
  default:
    break;
  }
}

void Board::update(void)
{
  if(gameState == GAME_RUNNING)
  {
    this->evalBoard();
    this->processBoard();

    gameFalling = this->getFalling();
    if(gameFalling.active == false)
    {
      this->addBlock();
    }
  }

  rowsMade = this->getRowsMade();
  totalRowsMade += rowsMade;
  bonus = rowsMade;
  modifier = (totalRowsMade / modifierGap) + 1;
  score += rowsMade * 10 * modifier * bonus;

  if((msProcessTime >= 50) && (rowsMade > 0))
  {
    msProcessTime = 250 - (modifier * 5);
  }

}

int Board::getDesiredFPS(void)
{
  return 60;
}

unsigned int* Board::getMsProcessTime(void)
{
  return &msProcessTime;
}

void Board::setVideoMemory(void* memory, int width, int height)
{
  videoMemPtr = memory;
  windowWidth = width;
  windowHeight = height;
  render.setWindowSize(windowWidth, windowHeight);
  render.setScreenBuffer(videoMemPtr);
}

void Board::draw(void)
{
  if(gameState == GAME_RUNNING)
  { 
    // Update the blocks on the board
    for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
      {
        BLOCK_TYPE type = board[i][j]->getBlockType();
        BlockDrawable *curBlock = new BlockDrawable(type, j + 1, i + 1);
        curBlock->id = j + (i * width);
        render.updateForeground(curBlock);
      }
    }

    render.run();
  }

  if(gameState == GAME_PAUSE)
  {
    //pos.X = 1;
    //pos.Y = 10;
    //SetConsoleCursorPosition(output, pos);
    //printf("********");
    //pos.X = 1;
    //pos.Y = 11;
    //SetConsoleCursorPosition(output, pos);
    //printf("  GAME  ");
    //pos.X = 1;
    //pos.Y = 12;
    //SetConsoleCursorPosition(output, pos);
    //printf(" PAUSED ");
    //pos.X = 1;
    //pos.Y = 13;
    //SetConsoleCursorPosition(output, pos);
    //printf("********");
  }

  if(gameState == GAME_END)
  {
    //pos.X = 1;
    //pos.Y = 10;
    //SetConsoleCursorPosition(output, pos);
    //printf("********");
    //pos.X = 1;
    //pos.Y = 11;
    //SetConsoleCursorPosition(output, pos);
    //printf("  GAME  ");
    //pos.X = 1;
    //pos.Y = 12;
    //SetConsoleCursorPosition(output, pos);
    //printf("  OVER  ");
    //pos.X = 1;
    //pos.Y = 13;
    //SetConsoleCursorPosition(output, pos);
    //printf("********");
  }
}

