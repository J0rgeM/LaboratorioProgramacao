final int windowWidth = 1200;
final int windowHeight = 500;

final color white = color(255,255,255);
final color black = color(0,0,0);
final color brown = color(139,69,19);
final color yellow = color(255, 255, 0);
final color green = color(0, 128, 0);
final color gray = color(192);

boolean hasBeenReleased = false;
int winner[] = {5, 5, 5, 5, 5};

PVector release;
PVector press;

float gravity = 0;
int counter = 0;

class Slingshot
{
  float x = 150;
  float y = 400;
  float w = 10;
  float h = 100;
  
  void draw()
  {
    fill(brown);
    rect(x, y, w, h);
    stroke(0);
    fill(black);
    triangle(x-(w/2), y-(w/2), x+(w/2), y, x+w+(w/2), y-(w/2));
  }
}

class Tree
{
  float x = 900;
  float y = 300;
  float w = 25;
  float h = 200;
  float r = 150;
  
  void draw()
  {
    fill(brown);
    rect(x, y, w, h);
    fill(green);
    circle(x+(w/2), y, r);
  }
}

class Bird
{
  float x;
  float y;
  float r;
  
  Bird(float x, float y, float r)
  {
    this.x = x;
    this.y = y;
    this.r = r;
  }
  
  void draw()
  {
    fill(brown);
    circle(x, y, r);
    fill(yellow);
    circle(x, y-(r/2), r/2);
  }
}

void settings()
{
 size(windowWidth, windowHeight);
}

Bird birds[];

Bird randomBird(float x, float y)
{
 return new Bird(x, y, 30); 
}

void update(float xc, float yc, float r)
{
  float x = random(xc-r, xc+r);
  float y = random(yc-r, yc+r);
  if((pow(x-xc,2))+(pow(y-yc,2)) < pow(r,2))
  {
    Bird b = randomBird(x, y);
    birds = (Bird[])append(birds, b);
  }
}

/*boolean check_collision_bird (Bird b) {
  return dist(b1.location.x,b1.location.y,b.location1.x,b.location1.y) < rs/2+rb/2;
}

int check_colision () {
  for (int i = 0; i < birds.length; i++) {
    if (check_collision_bird(birds[i]))
      return i;
  }
  return -1;
}*/

void birdDraw(Bird a[], int winner[])
{
  for(int i = 0; i < a.length; i++){
    if(i != winner[i] && winner[i] != 0)
      a[i].draw();
  }
}

void mousePressed()
{
  press = new PVector(mouseX, mouseY);
}

void keyPressed()
{
  if(key == 's')
  {
  float cSquared = sqrt(((mouseY-(400-(10/2)))*(mouseY-(400-(10/2))))+(((150+(10/2))-mouseX)*((150+(10/2))-mouseX)))/3;
  release = new PVector(mouseX, mouseY);
  press.sub(release);
  press.normalize();
  press.mult(cSquared);
  hasBeenReleased = true;
  gravity = 0; 
  }
  
  if(key == 'r')
  {
    for(int i = 0; i < 5; i++)
      winner[i] = 5;
  }
}

void BirdsTree()
{
  if(counter <= 5)
    update(900+(25/2), 300, 100/2);
    
  birdDraw(birds, winner);
  
  if(birds.length >= counter)
    counter++;
}

void ThrowSlingshhot()
{
  if(mousePressed)
  {
    slingshot.draw();
    tree.draw();
    birdDraw(birds, winner);
    
  fill(gray);
    circle(mouseX, mouseY, 20);
    stroke(255);
    line(150+(10/2), 400, mouseX, mouseY);
  }
  
  if(hasBeenReleased == true)
  {
    fill(gray);
    circle(release.x, release.y, 20);
    release.add(press);
    release.y += gravity;
    gravity += 0.6;
    
    for(int i = 0; i < birds.length; i++)
    {
      if(release.y <= (birds[i].y)+((birds[i].r)/2) && release.y >= (birds[i].y)-(((birds[i].r)/2)+(((birds[i].r)/2)/2)) && release.x <= (birds[i].x)+((birds[i].r)/2) && release.x >= (birds[i].x)-((birds[i].r)/2))
        winner[i] = i;
    }
  }
}

Slingshot slingshot = new Slingshot();
Tree tree = new Tree();

void setup()
{
  birds = new Bird[0];
} 

void draw()
{
  background(white);
  slingshot.draw();
  tree.draw();
  BirdsTree();
  ThrowSlingshhot();
  
    
}
