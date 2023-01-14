final int windowWidth = 640;
final int windowHeight = 480;

void settings()
{
  size(windowWidth, windowHeight);
}

class Ball
{
  int x;
  int y;
  int vx;
  int r;
  
  Ball(int x, int y, int r, int vx)
  {
    this.x = x;
    this.y = y;
    this.r = r;
    this.vx = vx;
  }
  
  void Update()
  {
    x += vx;
    
    if(vx > 0 && x-r > windowWidth)
      x = -r;
    else if(vx < 0 && x+r < 0)
      x = windowWidth + r;
  }
  
  void Draw()
  {
    ellipseMode(RADIUS);
    fill(255);
    circle(this.x, this.y, this.r);
  }
  
  void Draw(int x, int y)
  {
    ellipseMode(RADIUS);
    fill(255);
    circle(x, y, this.r);
  }
}

class BallBouncing extends Ball
{
  int vy;
  int ay = 1;
  
  BallBouncing(int x, int y, int r, int vx, int vy)
  {
    super(x, y, r, vx);
    this.vy = vy;
  }
  
  void Update()
  {
    if(mouseButton == RIGHT && mousePressed) return;
    super.Update();
    
    y += vy;
    
    if(y+r > windowHeight)
      vy = -vy;
    else
      vy += ay;
  }
  
  // inside BallBouncing
  void MouseDragged()
  {
    if(mouseButton == RIGHT)
      if(mouseX > x - r && mouseX < x + r && mouseY > y - r && mouseY < y + r)
      {
        x = mouseX;
        y = mouseY;
        vy = 0;
      }
    
  }
}

Ball ballA = new Ball(100, 100, 50, 2);
BallBouncing ballB = new BallBouncing(100, 200, 50, 2, 0);

void setup()
{
  
}

void mouseDragged()
{
  ballB.MouseDragged();
}

void draw()
{
  ballA.Update();
  ballB.Update();
  background(200);
  ballA.Draw(320, 240);
  ballB.Draw();
}
