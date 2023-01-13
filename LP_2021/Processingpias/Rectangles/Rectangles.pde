final int windowWidth = 640;
final int windowHeight = 480;

color red = color(255, 0, 0);
color blue = color(0, 0, 255);

class Rectangle
{
  int x;
  int y;
  int rWidth;
  int rHeight;
  int vel;
  color c;
  
  Rectangle(int x, int y, int vel, color c)
  {
    this.x = x;
    this.y = y;
    this.rWidth = 50;
    this.rHeight = 50;
    this.vel = vel;
    this.c = c;
  }
  
  void Update()
  {
    x+=vel;
    if(vel > 0 && (x >= windowWidth || x <= -rWidth))
      x = -rWidth;
    else if(vel < 0 && (x >= windowWidth || x <= -rWidth))
      x = windowWidth;
     
    if(frameCount % 60 == 0)
    {
      if(rHeight == 50)
        rHeight = 75;
      else
        rHeight = 50;
    }
  }
  
  void Draw()
  {
    fill(c);
    rect(x, y, rWidth, rHeight);
  }
}

void settings()
{
  size(windowWidth, windowHeight);
}

Rectangle a[] = new Rectangle[100];
int n = 0;

void CreateRectangle()
{
  int y = floor(random(450)); // random between 0-449, floor rounds float down to int
  int v = ceil(random(3));    // random between 1-3, ceil rounds float up to int
  color c = color(random(255), random(255), random(255)); // random color
  a[n++] = new Rectangle(0, y, v, c);
}

void setup()
{
  CreateRectangle();
}

void draw()
{
  background(200);
  for(int i = 0; i < n; i++)
  {
    a[i].Draw();
    a[i].Update();
  }

  if(frameCount % 10 == 0 && n < 100)
  {
    CreateRectangle();
  }
}
