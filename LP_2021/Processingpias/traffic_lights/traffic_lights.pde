//Window
final int windowWidth = 640;
final int windowHeight = 480;

//Colors
final color gray = color(200);
final color red = color(255,0,0);
final color yellow = color(250,170,50);
final color green = color(0,128,0);

int t = 0;

int x = (windowWidth)/2;
int y = (windowHeight)/2;

TrafficLights TLred = new TrafficLights(x,y-125,100,red);
TrafficLights TLyellow = new TrafficLights(x,y,100,yellow);
TrafficLights TLgreen = new TrafficLights(x,y+125,100,green);

class TrafficLights
{
  int x;
  int y;
  int d;
  color c;
  
  TrafficLights(int x, int y, int d, color c)
  {
    this.x = x;
    this.y = y;
    this.d = d;
    this.c = c;
  }
  
  void draw()
  {
    fill(c);
    circle(x,y,d);
  }
}

class RoadIntersection
{
  TrafficLights traffic[];
  
  RoadIntersection(TrafficLights traffic[])
  {
    this.traffic = traffic;
  }
  
  void draw()
  {
    for(int i = 0; i < traffic.length; i++)
      traffic[i].draw();
  }
}

void settings()
{
  size(windowWidth, windowHeight);
}

TrafficLights trafficlights[] = {TLred,TLyellow,TLgreen};
RoadIntersection lights;

void setup()
{
  lights = new RoadIntersection(trafficlights);
}

void draw()
{
  int t = frameCount/ 60 % 3;
  background(gray);
  lights.draw();
}
