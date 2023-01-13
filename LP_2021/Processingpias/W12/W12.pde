int windowWidth = 640;
int windowHeight = 480;

void settings()
{
  size(windowWidth, windowHeight);  
}


class Player
{
  int x;
  int y;
  int w;
  int h;
  color c;
  int v = 0;
  
  Player(int x, int y, int w, int h, color c)
  {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.c = c;
  }
  
  void KeyPressed()
  {
    if(key == 'a')
      v = -2;
    else if(key == 'd')
      v = 2;
  }
  
  void KeyReleased()
  {
    if(key == ' ')
    {
      projectiles[n++] = new Projectile(x+(w/2), y-10, 2);
    }
  }
  
  void Update()
  {
    if(!keyPressed)
      v = 0;
    
    x += v;
  }
  
  void Draw()
  {
    fill(c);
    rect(x, y, w, h);
    rect(x+w/3, y-10, w/3, 10);
  }
}


class Projectile
{
  int x;
  int y;
  int w = 3;
  int h = 10;
  int v;
  boolean deleted = false;
  
  Projectile(int x, int y, int v)
  {
    this.x = x;
    this.y = y;
    this.v = v;
  }
  
  void Update()
  {
    if(!deleted)
    {
      y -= v;
      
      if(enemy != null && x+w > enemy.x && x < enemy.x + enemy.w && y+h > enemy.y && y < enemy.y + enemy.h)
      {
        enemy = null;
        deleted = true;
      }
    }
  }
  
  void Draw()
  {
    if(!deleted)
    {
      fill(255);
      rect(x, y, w, h);
    }
  }
}


class Enemy
{
  int x;
  int y;
  int w = 60;
  int h = 60;
  int v;
  int cooldownFrames = 100;
  
  Enemy(int x, int y, int v)
  {
    this.x = x;
    this.y = y;
    this.v = v;
  }
  
  void Update()
  {
    x += v;
    
    if(x+w >= windowWidth || x < 0)
      v *= -1;
    
    if(cooldownFrames <= 0)
    {
      projectiles[n++] = new Projectile(x+(w/2), y+h, -2);
      cooldownFrames = ceil(random(100,240));
    }
    else
      cooldownFrames--;
  }
  
  void Draw()
  {
    fill(255);
    rect(x, y, w, h);
  }
}


void keyPressed()
{
  player.KeyPressed();
}

void keyReleased()
{
  player.KeyReleased();
}

Projectile[] projectiles = new Projectile[1000];
int n = 0;
Player player = new Player(windowWidth/2, windowHeight-30, 60, 20, color(0, 255, 0));
Enemy enemy = new Enemy(windowWidth/2, windowHeight/2, 2);

void setup()
{
  noStroke();
}

void update()
{
  player.Update();
  if(enemy != null)
    enemy.Update();
  
  for(int i = 0; i < n; i++)
  {
    projectiles[i].Update();
  }
}

void draw()
{
  update(); 
  background(0);
  player.Draw();
  if(enemy != null)
    enemy.Draw();
  
  for(int i = 0; i < n; i++)
  {
    projectiles[i].Draw();
  }
}
