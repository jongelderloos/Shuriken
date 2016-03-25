#ifndef DRAWABLE2D_H_
#define DRAWABLE2D_H_

class __declspec(dllexport) Drawable2D
{

public:
  Drawable2D();
  bool operator==(const Drawable2D&);
  virtual void Render(void*, int);
  
private:
  int id;
};

#endif // DRAWABLE2D_H_
