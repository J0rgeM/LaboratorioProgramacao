//Window
final int windowWidth = 640;
final int windowHeight = 480;

//Colors
final color gray = color(200);
final color black = color(0,0,0);
final color red = color(255,0,0);
final color yellow = color(250,170,50);

class Nigaro
{
  int x;
  int y;
  int rwidth;
  int rheight;
  color c;
  
  Nigaro (int x, int y, int rwidth, int rheight, color c)
  {
    this.x = x;
    this.y = y;
    this.rwidth = rwidth;
    this.rheight = rheight;
    this.c = c;
  }
  
  void Draw()
  {
    rect(x, y, rwidth, rheight);
  }
}

void settings ()
{
  size(windowWidth, windowHeight);
}

Nigaro a;

void setup()
{
  a = new Nigaro(100,100,50,50,red);
}

void draw()
{
  background(gray);
  noStroke();
  a.Draw();
  fill(red);
  
}
