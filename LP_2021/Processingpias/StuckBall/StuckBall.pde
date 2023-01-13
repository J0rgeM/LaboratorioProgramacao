int windowWidth = 640;
int windowHeight = 480;

color red = #FF0000;
color green = #00FF00;

class SBall
{
  int d;  //Ball's diameter
  color c;  //Ball's Color
  
  SBall(int d, color c)
  {
    this.d = d;
    this.c = c;
  }
  
  void Draw()
  {
    fill(c);
    circle(mouseX, mouseY, d);
  }
}

void settings()
{
  size(windowWidth, windowHeight);
}

SBall a;

void setup()
{
  a = new SBall(100, red);
}

void mousePressed()
{

}

void draw()
{
  background(200);
  if(a != null)
    a.Draw();
}
