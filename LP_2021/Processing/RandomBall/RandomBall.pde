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

Ball a[] = new Ball[1000];
int n = 0;

void setup()
{
  
}

void createBall()
{
  int x = floor(random(windowWidth));
  int y = floor(random(windowHeight));
  int d = floor(random(50, 250));
  color c = color(random(255), random(255), random(255));
  a[n++] = new Ball(x, y, d, c);
}

void keyPressed()
{
  if(key == 'n')
    createBall();
}

void draw()
{
  background(200);
  for(int i = 0; i < n; i++)
  {
    a[i].Draw();
  }
}
