#include "Block.h"
#include <stdlib.h>

Block::Block()
{
  type = (BLOCK_TYPE)((rand() % (NUM_BLOCK_TYPES-1)) + 1);
  evaluated = false;
}

Block::Block( BLOCK_TYPE t )
{
  type = t;
  evaluated = false;
}

Block Block:: operator=( const Block& other )
{
  (*this).type = other.getBlockType();
  (*this).evaluated = other.isEvaluated();

  return *this;
}

BLOCK_TYPE Block::getBlockType( void ) const
{
  return type;
}

void Block::setBlockType( BLOCK_TYPE t )
{
  type = t;
  evaluated = false;
}

bool Block::isEvaluated( void ) const
{
  return evaluated;
}

void Block::setEvaluated( bool e )
{
  evaluated = e;
}


