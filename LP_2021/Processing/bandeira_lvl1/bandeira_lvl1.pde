//Window
final int windowWidth = 640;
final int windowHeight = 480;

//Colors
final color gray = color(200);
final color black = color(0,0,0);
final color red = color(255,0,0);
final color yellow = color(250,170,50);

//Rectangles
final int x1 = 100;
final int y1 = 120;
Rectangle rec1 = new Rectangle(x1, 50, y1, 30, black);
Rectangle rec2 = new Rectangle(x1, 80, y1, 30, red);
Rectangle rec3 = new Rectangle(x1, 110, y1, 30, yellow);

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

  void Draw()
  {
    fill(c);
    rect(x, y, rWidth, rHeight);
  }
    
}

//Rectangle centered_at(int x, int y, int rWidth, int rHeight)
 // {
   // return new Rectangle(x-rWidth/2, y-rHeight/2);
  //}

void settings()
{
  size(windowWidth, windowHeight);
}

  Rectangle rectangle[] = {rec1,rec2,rec3};

void rectangleDraw(Rectangle a[], int n)
{
  for(int i = 0; i < n; i++)
    a[i].Draw();
}

void setup()
{
  
}

void draw()
{
  background(gray);
  noStroke();
  rectangleDraw(rectangle, 3);
}
