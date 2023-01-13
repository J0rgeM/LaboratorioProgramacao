final int windowWidth = 700;
final int windowHeight = 600;

final int humanversushuman = 0;
int modeWhoVersusWho = humanversushuman;  
int indexSFAP = 1;

// flags for the game logic
boolean humanMustMakeHisMove = true; // whose turn is it ? human / black = true
boolean PC_AI_is_Random = false; 
boolean showCountMove = true; 

int count = 0; // moves count for human versus human mainly  
final int rows = 6;
final int cols = 7;
// who won?
int winner = 0;
// the board
CircleButton[][] grid = new CircleButton[cols][rows];
int[][] gridChecker = new int[cols][rows];

// smaller vars
boolean locked = false;  
boolean gameOn = true;   // gets false when somebody wins 
PFont font;
int timer;
int countRed;
int countBlack;
int countDraw;

color yellow = color(255,204,0);
color black = color(0,0,0);
color white = color(255,255,255);
color red = color(255,0,0);
color gray = color(153);

class CountPieces {
  //
  int red=0;
  int black=0;
  int empty=0;
  PVector foundEmptyField = new PVector(-1, -1, 0);

  PVector countField (  int a, int b ) {
    int gridCell = gridChecker[a][b] ;

    switch (gridCell) {
    case 1: 
      red++; 
      break;
    case 2: 
      black++; 
      break;
    case 10: 
      empty++;
      foundEmptyField.x=a;
      foundEmptyField.y=b;
      break;
    default: 
      exit(); 
      break;
    } // switch
    return foundEmptyField;
  } // func 
} 
// =======================================================================

class CircleButton
{
  // class for the cells in the grid 
  color basecolor;
  int x, y;
  int size;
  color highlightcolor;
  color currentcolor;
  boolean highlight;
  boolean over = false;
  boolean pressed = false; 
  int moveCount = 0;

  CircleButton(int x, int y, int size, color currentcolor, color highlightcolor)
  { 
    this.x = x;
    this.y = y;
    this.size = size;
    this.highlightcolor = highlightcolor;
    this.currentcolor = currentcolor;
    highlight = true;
    moveCount = 0;
  }

  void setHighlightOff() {
    highlight = false;
  }
  
   boolean over()
  {
    if ( overCircle(x, y, size) ) {
      over = true;
      return true;
    }
    else {
      over = false;
      return false;
    }
  }
  
  void update()
  {
    if (over() && highlight) {
      currentcolor = highlightcolor;
    }
    else if (currentcolor == highlightcolor && !over()) {
      currentcolor = color(white);
    }
  }

  boolean pressed()
  {
    if (over) {
      locked = true;
      return true;
    }
    else {
      locked = false;
      return false;
    }
  }

  boolean overCircle(int x, int y, int diameter)
  {
    float disX = x - mouseX;
    float disY = y - mouseY;
    if (sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
      return true;
    }
    else {
      return false;
    }
  }

  void setColor(color a) {
    currentcolor = a;
    moveCount = count;
  }

  color getColor() {
    return currentcolor;
  }

  void display()
  {
    stroke(currentcolor);
    fill(currentcolor);
    ellipse(x, y, size, size);
    if (showCountMove) {
      if (currentcolor==color(red) || currentcolor==color(black)) {
        textSize(10); 
        text(moveCount, x+size/2, y+size/2);
      } // if
    } // if
  } // method 
  //
} // class 

void settings()
{
  size(windowWidth,windowHeight);
}

void smallSetup()
{
 
  for (int a = 0; a<cols; a++) {
    for (int b = 0; b<rows; b++) {
      gridChecker[a][b] = 10;
    }
  }
  
  for (int a = 0; a<cols; a++) {
    for (int b = 0; b<rows; b++) {
      grid[a][b] = new CircleButton(100*a + 50, 100*b + 50, 80, color(white), color(gray));
    }
  }
  color highlight = color(gray);
  ellipseMode(CENTER);
  count = 0;
  gameOn = true;
  timer=millis();
} // func 

void setup()
{
  background(yellow);
  smallSetup();
  smooth();
  font = createFont("Arial", 14);
}

void gameStuff() {
  // show board:
  // show lines 
  stroke(126);
  for ( int c = 1; c <= cols; c++) {
    line( c*(width/cols), 0, c*(width/cols), height);
  }
  for (int c = 1; c <= rows; c++) {
    line(0, c*(height/rows), width, c*(height/rows));
  }
  // show circles
  for (int c = 0; c<cols; c++) {
    for (int d = 0; d<rows; d++) {
      grid[c][d].display();
    }
  }
  
  // show win (if somebody won) : 
  if (checkWin() == true) {
    if (gameOn) 
      timer=millis();
    textFont(font, 65);
    if (winner == 4)
      shadowtext("Red Wins!", width/4, height/2, 3);
    else if (winner == 8)
      shadowtext("Black Wins!", width/3.5, height/2, 3);

    gameOn = false;
  } // if
  //
} 

void shadowtext (String s, float x, float y, int o)
{
  fill(100, 100);
  text(s, x+o, y+o);
  fill(58, 12, 247);
  text(s, x, y);
}

void update(int x, int y)
{
  // enter human move for human versus human
  if (mousePressed && gameOn) {
    for (int c = 0; c<cols; c++) {
      for (int d = 0; d<rows; d++) {
        if (grid[c][d].pressed() && (grid[c][d].getColor() == color(white)|| grid[c][d].getColor() == color(gray)) ) {
          if (d == 5 || (gridChecker[c][d + 1] == 1 || gridChecker[c][d+1] == 2)) {
            grid[c][d].setHighlightOff();
            count++;
            if (count % 2 == 1) {
              grid[c][d].setColor(color(red));
              gridChecker[c][d] = 1;
            }
            else {
              grid[c][d].setColor(color(black));
              gridChecker[c][d] = 2;
            }
          }
        }
      }
    }
  }
  if (locked == false && gameOn) {
    for (int c = 0; c<cols; c++) {
      for (int d = 0; d<rows; d++) {
        grid[c][d].update();
      }
    }
  }
  else {
    locked = false;
  }
}

void playGame() 
{
  update(mouseX, mouseY);
  gameStuff(); 
} 

void draw()
{
   playGame();
} 

boolean checkDraw()
{
  int test=0;
  for (int a=0; a < rows; a++) {
    for (int b=0; b < cols; b++) {
      if (gridChecker[b][a] == 1 ||  gridChecker[b][a] == 2)
        test++;
    }
  }
  return (test>=rows*cols);
}

boolean checkWin()
{
  //horizontal
  for (int a=0; a < rows; a++) {
    for (int b=0; b < cols-3; b++) {
      int tCheck = (gridChecker[b][a]) + (gridChecker[b+1][a]) + (gridChecker[b+2][a]) + (gridChecker[b+3][a]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }
  //vertical
  for (int a=0; a < rows-3; a++) {
    for (int b=0; b < cols; b++) {
      int tCheck = (gridChecker[b][a]) + (gridChecker[b][a+1]) + (gridChecker[b][a+2]) + (gridChecker[b][a+3]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }

  //diagonals
  for (int a=0; a < rows-3; a++) {
    for (int b=0; b < cols-3; b++) {
      int tCheck = (gridChecker[b][a]) + (gridChecker[b+1][a+1]) + (gridChecker[b+2][a+2]) + (gridChecker[b+3][a+3]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }

  for (int a=0; a < rows-3; a++) {
    for (int b=3; b < cols; b++) {
      int tCheck = (gridChecker[b][a]) + (gridChecker[b-1][a+1]) + (gridChecker[b-2][a+2]) + (gridChecker[b-3][a+3]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }
  return false;
}

// -------------------------------------------------------------



boolean checkPattern( int findRed, int findBlack, int findEmpty )
{
  // A powerful function that checks 4 cells next to each other and
  // when a given pattern is matched sets any empty cell within the row. 
  // A pattern is a combination like 2 red, 0 black and 2 empty cells.
  // The order of the cells is not defined. 
  // Which empty cell is chosen is also not said.
  //  
  // For this function the sum must be 4 (he checks only 4 cells). 
  //
  if ((findRed + findBlack + findEmpty) != 4) {
    exit(); // code error
  } 
  //
  CountPieces counter = new CountPieces ();  // int findRed, int findBlack, int findEmpty
  //
  //horizontal
  for (int a=0; a < rows; a++) {
    for (int b=0; b < cols-3; b++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(b, a) ;
      counter.countField(b+1, a) ;
      counter.countField(b+2, a) ;
      counter.countField(b+3, a) ;
      // does pattern match ?
      if (counter.red==findRed && counter.black == findBlack && counter.empty == findEmpty) {
        // counter.display (); 
        // has an empty field been found? 
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            return true;
          }
        }
      }
    }
  }

  //vertical
  for (int a=0; a < rows-3; a++) {
    for (int b=0; b < cols; b++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(b, a) ;
      counter.countField(b, a+1) ;
      counter.countField(b, a+2) ;
      counter.countField(b, a+3) ;
      // does pattern match ?
      if (counter.red==findRed && counter.black == findBlack && counter.empty == findEmpty) {
        // counter.display (); 
        // has an empty field been found?
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            return true;
          }
        }
      }
    }
  }
  //
  // diagonals
  for (int a=0; a < rows-3; a++) {
    for (int b=0; b < cols-3; b++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(b, a) ;
      counter.countField(b+1, a+1) ;
      counter.countField(b+2, a+2) ;
      counter.countField(b+3, a+3) ;
      // does pattern match ?
      if (counter.red==findRed && counter.black == findBlack && counter.empty == findEmpty) {
        // counter.display (); 
        // has an empty field been found?
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            return true;
          }
        }
      }
    }
  }

  for (int a=0; a < rows-3; a++) {
    for (int b=3; b < cols; b++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(b, a) ;
      counter.countField(b-1, a+1) ;
      counter.countField(b-2, a+2) ;
      counter.countField(b-3, a+3) ;
      // does pattern match ?
      if (counter.red==findRed && counter.black == findBlack && counter.empty == findEmpty) {
        // counter.display (); 
        // has an empty field been found?
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

boolean makeMove ( int c, int d  ) {
  boolean doneMakeMove = false;  
  for (int d1 = 0; d1<rows; d1++) {
    if ( (grid[c][d1].getColor() == color(white) || grid[c][d1].getColor() == color(153)) ) {
      if (d1 == 5 || (gridChecker[c][d1 + 1] == 1 || gridChecker[c][d1+1] == 2)) {
        if (d==d1) {
          grid[c][d].setHighlightOff();
          count++;
          grid[c][d].setColor(colorFromPlayer(humanMustMakeHisMove));
          gridChecker[c][d] = intFromPlayer(humanMustMakeHisMove);
          doneMakeMove = true;
        }
      }
    }
  }
  return doneMakeMove;
  //
}

// -----------------------------------------------------------------------

// minor tools: these tools evaluate humanMustMakeHisMove in different ways
color colorFromPlayer(boolean humanMustMakeHisMove) {
  // the color a red or black cell has
  if (humanMustMakeHisMove) 
    return color(red); // red
  else 
    return color(black);
}

int intFromPlayer(boolean humanMustMakeHisMove) {
  // the value a red or black cell has
  if (humanMustMakeHisMove) 
    return 1; // 1 
  else 
    return 2; // 2
}

String stringFromPlayer(boolean humanMustMakeHisMove) {
  // text of the player
  if (humanMustMakeHisMove) 
    return "red";   //  1 
  else 
    return "black"; // 2
}

int winnerFromPlayer(boolean humanMustMakeHisMove) {
  // the count for detecting a win 
  if (humanMustMakeHisMove) 
    return 4;   // red
  else 
    return 8;   // black
}
