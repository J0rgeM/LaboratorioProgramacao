final int windowWidth = 640;
final int windowHeight = 480;

class Rectangle
{
  int x;
  int y;
  int rWidth;
  int rHeight;
  int vel;
  
  Rectangle(int x, int y, int rWidth, int rHeight, int vel)
  {
    this.x = x;
    this.y = y;
    this.rWidth = rWidth;
    this.rHeight = rHeight;
    this.vel = vel;
  }
  
  void Update()
  {
    x+=vel;
    if(vel > 0 && (x >= windowWidth || x <= -rWidth))
      x = -rWidth;
    else if(vel < 0 && (x >= windowWidth || x <= -rWidth))
      x = windowWidth;
  }
  
  void Draw()
  {
    rect(x, y, rWidth, rHeight);
  }
}

void settings()
{
  size(windowWidth, windowHeight);
}

Rectangle a;
Rectangle b;

void setup()
{
  a = new Rectangle(100, 100, 30, 30, 1);
  b = new Rectangle(540, 260, 30, 50, -3);
}

void draw()
{
  background(127);
  a.Draw();
  b.Draw();
  a.Update();
  b.Update();
}
