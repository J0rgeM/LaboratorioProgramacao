final int windowHeight = 480;
final int windowWidth = 2 * windowHeight;

final color red = color(255, 0, 0);
final color white = color(255, 255, 255);
final color yellow = color(255, 255, 0);
final color green = color(0, 128, 0);
final color blue = color(0, 0, 255);

final float acceleration = -0.01;
float radius = 32;

class Ball {
  PVector o;
  final float r;
  final float m;
  PVector v;
  final color c;
  final boolean dot;

  Ball(float x, float y, float r, float m, float vx, float vy, color c, boolean dot)
  {
    this.o = new PVector(x, y);
    this.r = r;
    this.m = m;
    this.v = new PVector(vx, vy);
    this.c = c;
    this.dot = dot;
  }

  void draw()
  {
    pushMatrix();
    noStroke();
    fill(c);
    circle(o.x, o.y, 2*r);
    if (dot)
    {
      stroke(0);
      strokeWeight(4);
      point(o.x + r/2, o.y + r/2);
    }
    popMatrix();
  }

  void move()
  {
    o = PVector.add(o, v);
  }

  void stop()
  {
    o.set(0, 0);
  }

  void shoot(float vx, float vy)
  {
    v.add(vx, vy);
  }

  boolean contains(float x, float y)
  {
    return dist(o.x, o.y, x, y) <= r;
  }

  boolean stopped()
  {
    return v.x == 0 && v.y == 0;
  }


  void drag()
  {
    if (!stopped())
    {
      float m = v.mag();
      float m1 = constrain(m + acceleration, 0, m); // note: accelaration is negative
      v.mult(m1/m);
    }
  }

  void moveInside()
  {
    move();
    if (o.x+r > width)
    {
      o.x = width-r;
      v.x = -v.x;
    }
    if (o.y+r > height)
    {
      o.y = height-r;
      v.y = -v.y;
    }
    if (o.x-r < 0)
    {
      o.x = r;
      v.x = -v.x;
    }
    if (o.y-r < 0)
    {
      o.y = r;
      v.y = -v.y;
    }
    drag();
  }  

  boolean collide(Ball other)
  {
    return PVector.sub(o, other.o).magSq() < sq(r + other.r);
  }

  // See https://en.wikipedia.org/wiki/Elastic_collision
  PVector velocityAfterCollision(Ball other)
  {
    float k = 2 * other.m / (m + other.m);
    float num = PVector.sub(v, other.v).dot(PVector.sub(o, other.o));
    float den = PVector.sub(o, other.o).magSq();
    PVector result = PVector.sub(v, PVector.mult(PVector.sub(o, other.o), k * num / den));
    return result;
  }
}

void collision(Ball b1, Ball b2)
{
  PVector v1 = b1.velocityAfterCollision(b2);
  PVector v2 = b2.velocityAfterCollision(b1);
  b1.v = v1;
  b2.v = v2;
  while (b1.collide(b2))
  {
    b1.move();
    b2.move();
  }
}

Ball b1, b2, br;
int mouseX0, mouseY0;
boolean shooting1 = false;
boolean shooting2 = false;

void mousePressed()
{
  mouseX0 = mouseX;
  mouseY0 = mouseY;
  println("+++", mouseX0, mouseY0);
}

void mouseReleased()
{
  if (shooting1)
    b1.shoot((b1.o.x - mouseX)/32, (b1.o.y - mouseY)/32);
  if (shooting2)
    b2.shoot((b2.o.x - mouseX)/32, (b2.o.y - mouseY)/32);
}

void mouseDragged()
{
  //stroke(0);
  //line(mouseX, mouseY, mouseX0, mouseY0);
  //println(mouseX, mouseY);
}

void settings()
{
  size(windowWidth, windowHeight);
}

void setup()
{
  b1 = new Ball(width/3, height/2, 32, 1, 0, 0, white, false);
  b2 = new Ball(2*width/3, height/3, 32, 1, 0, 0, white, true);
  br = new Ball(2*width/3, 2*height/3, 32, 1, 0, 0, red, false);
}

void draw()
{ 
  update();
  background(green);
  stroke(200);
  strokeWeight(4);
  if (shooting1)
    line(mouseX, mouseY, b1.o.x, b1.o.y);
  if (shooting2)
    line(mouseX, mouseY, b2.o.x, b2.o.y);
  b1.draw();
  b2.draw();
  br.draw();
}

void update()
{
  boolean test[] = {true, true, true};
  if (b1.collide(b2))
  {
    collision(b1, b2);
    test[0] = false;
    test[1] = false;
  } else if (b1.collide(br))
  {
    collision(b1, br);
    test[0] = false;
    test[2] = false;
  } else if (b2.collide(br))
  {
    collision(b2, br);
    test[1] = false;
    test[2] = false;
  };
  if (test[0])
    b1.moveInside();
  if (test[1])
    b2.moveInside();
  if (test[2])
    br.moveInside();
  boolean allStopped = b1.stopped() && b2.stopped() && br.stopped();
  shooting1 = allStopped && mousePressed && b1.contains(mouseX0, mouseY0) && !b1.contains(mouseX, mouseY);
  shooting2 = allStopped && mousePressed && b2.contains(mouseX0, mouseY0) && !b2.contains(mouseX, mouseY);
}
