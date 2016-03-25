#include "Drawable2D.h"

Drawable2D::Drawable2D()
{
}

void Drawable2D::Render(void*, int)
{
}

// TODO: inline
bool Drawable2D::operator==(const Drawable2D& other)
{
  return (id == other.id);
}
