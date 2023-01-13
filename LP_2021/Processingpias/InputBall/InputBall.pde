int windowWidth = 640;
int windowHeight = 480;

color red = #FF0000;
color green = #00FF00;

class Ball
{
  int x;  //Ball's x position
  int y;  //Ball's y position
  int d;  //Ball's diameter
  color c;  //Ball's Color
  
  Ball(int x, int y, int d, color c)
  {
    this.x = x;
    this.y = y;
    this.d = d;
    this.c = c;
  }
  
  // Dentro da classe
  
  void MousePressed()
  {
    if(mouseButton == LEFT)
    {
      if(c == red)
        c = green;
      else
        c = red;
    }
  }
  
  void Draw()
  {
    fill(c);
    circle(x, y, d);
  }
}

void settings()
{
  size(windowWidth, windowHeight);
}

Ball a;

void setup()
{
  a = new Ball(windowWidth/2, windowHeight/2, 100, red);
}



void mousePressed()
{
  a.MousePressed();
  if(mouseButton == RIGHT)
  {
      a = new Ball(mouseX, mouseY, 100, red);
  }
}

void draw()
{
  background(200);
  if(a != null)
    a.Draw();
}
