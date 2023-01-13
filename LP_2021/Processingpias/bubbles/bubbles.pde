final int windowWidth = 640;
final int windowHeight = 480;

color lightblue = color(173,216,230);
color red = color(255,0,0);

class Bubble
{
  int x;
  int y;
  int rWidth;
  int rHeight;
  color c;
  int vel;
  
  Bubble(int x, int y, int rWidth, int rHeight, color c, int vel)
  {
    this.x = x;
    this.y = y;
    this.rWidth = rWidth;
    this.rHeight = rHeight;
    this.c = c;
    this.vel = vel;
  }
  void update()
  {
   y++;
    
  }
  void draw()
  {
    fill(c);
    ellipse(x,y,rWidth,rHeight);
  }
}
void settings()
{
  size(windowWidth, windowHeight);
}

//Bubble bolha = new Bubble(250,480,50,50,red);
Bubble bolha[] = new Bubble[100];
int n = 0;

void CreateBubble()
{
  int y = floor(random(450)); // random between 0-449, floor rounds float down to int
  int v = ceil(random(3));    // random between 1-3, ceil rounds float up to int
 color c = color(random(255), random(255), random(255)); // random color
  bolha[n++] = new Bubble(0, y, v, c, 3, red);
}

void setup()
{
  CreateBubble();
}

void draw()
{
 background(lightblue);
 for(int i = 0; i < n; i++)
  {
    bolha[i].draw();
   // bolha[i].update();
  }

}
