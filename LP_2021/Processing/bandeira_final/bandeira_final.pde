//Window
final int windowWidth = 640;
final int windowHeight = 480;

//Colors
final color gray = color(200);
final color black = color(0,0,0);
final color red = color(255,0,0);
final color yellow = color(250,170,50);
final color white = color(255,255,255);
final color blue_netherlands = color(33,70,139);
final color red_sparking = color(174,28,40);
final color red_austria = color(237, 41, 57);
final color blue_argentina = color(117,170,219);

int t = 0;

int x = (windowWidth-120)/2;
int y = (windowHeight-90)/2;

//Germany
Rectangle rec1 = new Rectangle(x-60-133/2, y-100, 120, 30, black);
Rectangle rec2 = new Rectangle(x-60-133/2, y+30-100, 120, 30, red);
Rectangle rec3 = new Rectangle(x-60-133/2, y+60-100, 120, 30, yellow);

//Argentina
Rectangle rec10 = new Rectangle(x-60-133/2,y-100,120,30,blue_argentina);
Rectangle rec11 = new Rectangle(x-60-133/2,y+30-100,120,30,white);
Rectangle rec12 = new Rectangle(x-60-133/2,y+60-100,120,30,blue_argentina);

//Austria
Rectangle rec4 = new Rectangle(x-60-133/2,y-100,120,30,red_austria);
Rectangle rec5 = new Rectangle(x-60-133/2,y+30-100,120,30,white);
Rectangle rec6 = new Rectangle(x-60-133/2,y+60-100,120,30,red_austria);

//Netherlands
Rectangle rec7 = new Rectangle(x-60-133/2,y-100,120,30,red_sparking);
Rectangle rec8 = new Rectangle(x-60-133/2,y+30-100,120,30,white);
Rectangle rec9 = new Rectangle(x-60-133/2,y+60-100,120,30,blue_netherlands);

class Rectangle
{
  int x;
  int y;
  int rWidth;
  int rHeight;
  color c;
  
  Rectangle(int x, int y, int rWidth, int rHeight, color c)
  {
    this.x = x;
    this.y = y;
    this.rWidth = rWidth;
    this.rHeight = rHeight;
    this.c = c;
  }

  //void draw()
  //{
   // fill(c);
    //rect(x, y, rWidth, rHeight);
 // }
  
  void draw(float dx, float dy)
  {
    fill(c);
    rect(x+dx, y+dy, rWidth, rHeight);  
  }
}

class Flag 
{
  Rectangle rect [];
  
  Flag( Rectangle rect[])
  {
    this.rect = rect;
  }
  
  //void draw()
  //{
    //for(int i = 0; i < rect.length; i++)
     // rect[i].draw();
  //}
  
  void draw(float dx, float dy)
  {
    for(int i = 0; i < rect.length; i++)
      rect[i].draw(dx, dy);
  }
}

void settings()
{
  size(windowWidth, windowHeight);
}

  float posx_germany[] = {0,253,253,0};
  float posy_germany[] = {0,0,190,190};

  float posx_argentina[] = {253,253,0,0};
  float posy_argentina[] = {0,190,190,0};
  
  float posx_netherlands[] = {0,0,253,253};
  float posy_netherlands[] = {190,0,0,190};
  
  float posx_austria[] = {253,0,0,253};
  float posy_austria[] = {190,190,0,0};

  Rectangle rect_germany[] = {rec1,rec2,rec3};
  Flag germany;
  
  Rectangle rect_austria[] = {rec4,rec5,rec6};
  Flag austria;
  
  Rectangle rect_netherlands[] = {rec7,rec8,rec9};
  Flag netherlands;

  Rectangle rect_argentina[] = {rec10,rec11,rec12};
  Flag argentina;
  
void setup()
{
  germany = new Flag(rect_germany);
  austria = new Flag(rect_austria);
  netherlands = new Flag(rect_netherlands);
  argentina = new Flag(rect_argentina);
}

void draw()
{
  int t = frameCount/ 120 % 4;
  background(gray);
  noStroke();
  germany.draw(posx_germany[t], posy_germany[t]);
  netherlands.draw(posx_netherlands[t], posy_netherlands[t]);
  austria.draw(posx_austria[t], posy_austria[t]);
  argentina.draw(posx_argentina[t], posy_argentina[t]);
}
