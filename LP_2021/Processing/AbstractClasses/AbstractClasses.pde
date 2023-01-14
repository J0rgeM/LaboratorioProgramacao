final int windowWidth = 640;
final int windowHeight = 480;

void settings()
{
  size(windowWidth, windowHeight);
}

abstract class Enemy
{
  int x;
  int y;
  int r;
  
  Enemy(int x, int y, int r)
  {
    this.x = x;
    this.y = y;
    this.r = r;
  }
  
  abstract void Draw();
}

class Goblin extends Enemy
{
  Goblin(int x, int y, int r)
  {
    super(x, y, r);
  }
  
  void Draw()
  {
    rectMode(RADIUS);
    fill(0, 220, 0);
    rect(x, y, r, r);
  }
}

class Skeleton extends Enemy
{
  Skeleton(int x, int y, int r)
  {
    super(x, y, r);
  }
  
  void Draw()
  {
    rectMode(RADIUS);
    fill(255, 255, 240);
    rect(x, y, r, 2*r);
  }
}

class Orc extends Enemy
{
  Orc(int x, int y, int r)
  {
    super(x, y, r);
  }
  
  void Draw()
  {
    ellipseMode(RADIUS);
    fill(0, 100, 0);
    circle(x, y, r);
  }
}

Enemy[] enemies = {new Goblin(260, 240, 25), 
                  new Skeleton(320, 240, 25), 
                  new Orc(380, 240, 30)};

void setup()
{
  
}

void draw()
{
  background(200);
  
  for(int i = 0; i < enemies.length; i++)
    enemies[i].Draw();
}
