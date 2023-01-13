final int windowWidth = 640;
final int windowHeight = 480;

color lightblue = color(173,216,230);
color red = color(255,0,0);
color white = color(255,255,255);
color black = color(0,0,0);
color purple = color(153,51,153);
color yellow = color(255,255,0);
color rose = color(255,203,219);
color silver = color(192,192,192);

class Fish
{
  int x;
  int y;
  int rWidth;
  int rHeight;
  int vel;
  color c;
  
  Fish(int x, int y, int rWidth, int rHeight,int vel, color c)
  {
    this.x = x;
    this.y = y;
    this.rWidth = rWidth;
    this.rHeight = rHeight;
    this.vel = vel;
    this.c = c;
  }
  
  void update()
  {
    x+=vel;
    if(vel > 0 && x >= windowWidth)
      x = -rWidth;
    else if(vel < 0 && x <= -rWidth)
      x = windowWidth;
  }
  
   void draw()
  {
    noStroke();
    fill(c);
    ellipse(x, y, rWidth, rHeight);
    if(vel > 0)
    {
      triangle( x-rWidth/2,y , x-rWidth,y+rHeight/3 , x-rWidth,y-rHeight/3);
      fill(black);
      circle( x+rWidth*2/6, y-rHeight/4,10);
      stroke(0);
      line(x,y+rHeight/4 ,x+rWidth/3,y+rHeight/4);
    }
    else 
    {
      triangle( x+rWidth/2,y , x+rWidth,y-rHeight/3 , x+rWidth,y+rHeight/3);
      fill(black);
      circle( x-rWidth*2/6, y-rHeight/4,10);
      stroke(0);
      line(x,y+rHeight/4 ,x-rWidth/3,y+rHeight/4);
    }      
  }
}

class Sardine extends Fish
{
  Sardine(int x, int y)
  {
    super(x,y,60,20,3,silver);
  }
}

Sardine sardinha[] = new Sardine[16];
int n = 0;

void CreateSardine(int xcir, int ycir, int raio)
{
  int i = 0;
  while(i < 16)
  {
    int x = ceil(random(xcir - raio, xcir + raio));
    int y = ceil(random(ycir - raio, ycir + raio));
    if(((pow(x-xcir,2) + pow(y-ycir,2)) < pow(raio,2)))
      {
        sardinha[n++] = new Sardine(x,y);
        i++;
      }
   } 
}

class Bubble
{
  float x;
  float y;
  float extend;
  
  Bubble(float x, float y, float extend)
  {
   this.x = x;
   this.y = y;
   this.extend = extend;
  }
  
  void update()
  {
    y -= 30/extend;
    if(y < 0)
      y = windowHeight + extend;
  }
  
  void draw()
  {
   fill(255, 40);
   stroke(255);
   circle(x, y, extend);
  }
}

void settings()
{
  size(windowWidth, windowHeight);
}

Fish peixe1 = new Fish(0, 80, 150, 50, 1, red);
Fish peixe2 = new Fish(20, 180, 50, 50, 2, purple);
Fish peixe3 = new Fish(400, 270, 75, 75, -2, yellow);
Fish peixe4 = new Fish(100, 300, 50, 150, 3, rose);

Fish aquario[] = {peixe1, peixe2, peixe3, peixe4};

Bubble bolha1 = new Bubble(random(windowWidth), windowHeight, random(100));
Bubble bolha2 = new Bubble(random(windowWidth), windowHeight, random(100));
Bubble bolha3 = new Bubble(random(windowWidth), windowHeight, random(100));
Bubble bolha4 = new Bubble(random(windowWidth), windowHeight, random(100));
Bubble bolha5 = new Bubble(random(windowWidth), windowHeight, random(100));

Bubble bolhas[] = {bolha1, bolha2, bolha3, bolha4, bolha5};

void setup()
{
  CreateSardine(100,200,60);
  aquario = (Fish[])concat(aquario, sardinha);
}

void drawAquario()
{
  for(int i = 0; i < aquario.length; i++)
  {
    aquario[i].draw();
    aquario[i].update();
  }
}

void drawBolhas()
{
  for(int i = 0; i < bolhas.length; i++)
  {
    bolhas[i].draw();
    bolhas[i].update();
  }
}

void draw()
{
  background(lightblue);
  drawAquario();
  drawBolhas();
}
