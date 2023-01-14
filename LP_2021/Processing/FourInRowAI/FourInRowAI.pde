// window
final int windowWidth = 700;
final int windowHeight = 600;

// vars for the game logic
// human versus human OR human versus PC OR PC vs. PC?
final int humanversushuman = 0;
final int humanversusPC = 1;
final int PCversusPC = 2;

// speed For Auto Play (when playing PCversusPC)  
int[] speedForAutoPlay = {0, 92, 2000, 4000};
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
int countYellow;
int countDraw;

//colors
final color yellow = color(255,204,0);
final color black = color(0,0,0);
final color white = color(255,255,255);
final color red = color(255,0,0);
final color gray = color(153);
final color blue = color(0,128,255);

void settings()
{
  size(windowWidth, windowHeight);
  smooth();
}

void setup()
{
  // runs only once
  font = createFont("Arial", 14);
  smallSetup();
}

void smallSetup() 
{
  // runs every time a new game is started
  background(blue);
  for (int i = 0; i<cols; i++) {
    for (int j = 0; j<rows; j++) {
      gridChecker[i][j] = 10;
    }
  }

  for (int i = 0; i<cols; i++) {
    for (int j = 0; j<rows; j++) {
      grid[i][j] = new CircleButton(100*i + 50, 100*j + 50, 80, color(white), color(gray));
    }
  }

  color highlight = color(gray);
  ellipseMode(CENTER);
  println("New game.");
  count = 0;
  gameOn = true;
  timer = millis();
} // func 

void draw()
{
  playGame();
} 

void keyPressed()
{
  switch(key)
  {
  case 'n':
  case 'N':
    smallSetup();
    break;
    
  case 's':
  case 'S':
    indexSFAP++;
    if (indexSFAP>=speedForAutoPlay.length)
      indexSFAP=0;
    break;
    
  default:
    // do nothing 
    break;
  } // switch
  //
}

void playGame()
{
    if (gameOn) 
    {
      if (timer+speedForAutoPlay[indexSFAP] < millis())
      {
        timer=millis();
        if (count % 2 == 0)
        {
          humanMustMakeHisMove=true; // red 
          PC_AI_is_Random=true;  // AI 
        }
        else 
        {
          humanMustMakeHisMove=false; // black
          PC_AI_is_Random=true;   // no AI
        }
        // ---- make move
        if (PC_AI_is_Random)
          updatePCMoveForHumanVersusPC_Random();
        else 
          updatePCMoveForHumanVersusPC_WinFinder();
      } // if timer
    } // if gameOn
    if (!gameOn) {
      if (timer+speedForAutoPlay[indexSFAP] < millis())
      {
        smallSetup();
        // auto play 
        gameOn = true;
        timer = millis();
      }
    }
  gameStuff();
}

void gameStuff()
{
  // show board:
  // show lines 
  stroke(126);
  for ( int i = 1; i <= cols; i++) {
    line( i*(width/cols), 0, i*(width/cols), height);
  }
  for (int j = 1; j<=rows; j++) {
    line(0, j*(height/rows), width, j*(height/rows));
  }
  // show circles
  for (int i = 0; i<cols; i++) {
    for (int j = 0; j<rows; j++) {
      grid[i][j].display();
    }
  }
  // show score 
  fill(black);
  textSize(10);
  text(countRed+":"+countYellow+" and draws: "+countDraw, width-200, 30);
  //
  // draw
  if (checkDraw ()) {
    println ("Draw");
    countDraw++;
    gameOn = false;
  }
  // show win (if somebody won) : 
  if (checkWin() == true) {
    if (gameOn) 
      timer=millis();
    textFont(font, 65);
    if (winner == 4) {
      shadowtext("Red Wins!", width/4, height/2, 3);
      if (gameOn) println ("Red Wins!");
      if (gameOn) countRed++;
    }
    else if (winner == 8) {
      shadowtext("Yellow Wins!", width/3.5, height/2, 3);
      if (gameOn) println ("Yellow Wins!");
      if (gameOn) countYellow++;
    }
    gameOn = false;
  } // if
} // func 

void shadowtext (String s, float x, float y, int o)
{
  fill(100, 100);
  text(s, x+o, y+o);
  fill(58, 12, 247);
  text(s, x, y);
}

// -------------------------------------------------------------

boolean checkDraw() {
  int test=0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (gridChecker[j][i] == 1 ||  gridChecker[j][i] == 2)
        test++;
    }
  }
  return (test>=rows*cols);
}

boolean checkWin()
{
  //horizontal
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols-3; j++) {
      int tCheck = (gridChecker[j][i]) + (gridChecker[j+1][i]) + (gridChecker[j+2][i]) + (gridChecker[j+3][i]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }

  //vertical
  for (int i = 0; i < rows-3; i++) {
    for (int j = 0; j < cols; j++) {
      int tCheck = (gridChecker[j][i]) + (gridChecker[j][i+1]) + (gridChecker[j][i+2]) + (gridChecker[j][i+3]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }

  //diagonals
  for (int i = 0; i < rows-3; i++) {
    for (int j = 0; j < cols-3; j++) {
      int tCheck = (gridChecker[j][i]) + (gridChecker[j+1][i+1]) + (gridChecker[j+2][i+2]) + (gridChecker[j+3][i+3]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }

  for (int i = 0; i < rows-3; i++) {
    for (int j = 3; j < cols; j++) {
      int tCheck = (gridChecker[j][i]) + (gridChecker[j-1][i+1]) + (gridChecker[j-2][i+2]) + (gridChecker[j-3][i+3]);
      if (tCheck == 8 || tCheck == 4)
      {
        winner = tCheck;
        return true;
      }
    }
  }
  return false;
}

void updatePCMoveForHumanVersusPC_Random()
{
  // PC Move for human versus PC - random 
  boolean donePC = false;
  //
  if (gameOn) { 
    // try 50 times to find a position 
    for (int x = 0; x < 50; x++) {
      // choose a position via random
      int i = int(random(cols));
      for (int j = 0; j < rows; j++) {
        if ( (grid[i][j].getColor() == color(white) || grid[i][j].getColor() == color(gray)) ) {
          if (j == 5 || (gridChecker[i][j + 1] == 1 || gridChecker[i][j+1] == 2)) {
            grid[i][j].setHighlightOff();
            count++;
            grid[i][j].setColor(colorFromPlayer(humanMustMakeHisMove));
            gridChecker[i][j] = intFromPlayer(humanMustMakeHisMove);
            donePC = true;
          }
        }
      } // for 
      if (donePC) 
        break;
    } // for 
    //
    // in the unlikely case he didn't find any position via random
    if (!donePC)  
    {
      println ("couldn't find PC Move - now try linear. ");
      for (int c=0; c<cols; c++) {
        for (int d = 0; d<rows; d++) {
          if ( (grid[c][d].getColor() == color(white) || grid[c][d].getColor() == color(gray)) ) {
            if (d == 5 || (gridChecker[c][d + 1] == 1 || gridChecker[c][d+1] == 2)) {
              grid[c][d].setHighlightOff();
              count++;
              grid[c][d].setColor(colorFromPlayer(humanMustMakeHisMove));
              gridChecker[c][d] = intFromPlayer(humanMustMakeHisMove);
              donePC = true;
            }
          }
        } // for 
        if (donePC) 
          break;
      } // for
    } // if
    //
    // in the very unlikely case he didn't find any position at all
    if (!donePC) 
      println ("couldn't find a PC Move. ");
    //
    if (locked == false && gameOn) {
      for (int c2 = 0; c2<cols; c2++) {
        for (int d = 0; d<rows; d++) {
          grid[c2][d].update();
        }
      }
    }
    else {
      locked = false;
    }
  }
  humanMustMakeHisMove = true;
}

void updatePCMoveForHumanVersusPC_WinFinder()
{
  // PC Move for human versus PC - win finder  
  boolean donePC = false;
  //
  if (gameOn) { 
    // AI
    //
    // choose a position via going from left to right
    // simulate move of the PC
    for (int c=0; c<cols; c++) {
      if (!donePC) {
        for (int d = 0; d<rows; d++) {
          if ( (grid[c][d].getColor() == color(white) || grid[c][d].getColor() == color(gray)) ) {
            if (d == 5 || (gridChecker[c][d + 1] == 1 || gridChecker[c][d+1] == 2)) {
              // save 
              int oldgridChecker = gridChecker[c][d];
              // make move 
              grid[c][d].setHighlightOff();
              grid[c][d].setColor(colorFromPlayer(humanMustMakeHisMove));
              gridChecker[c][d] = intFromPlayer(humanMustMakeHisMove);
              // win? 
              if (checkWin() == true) {
                if (winner == winnerFromPlayer(humanMustMakeHisMove)) {
                  // good move
                  donePC = true;
                  winner = 0;
                  count++;
                  grid[c][d].moveCount = count;
                  println ("AI winning move found");
                } // if
              } // if
              if (!donePC) {
                // restore 
                gridChecker[c][d] = oldgridChecker;
                grid[c][d].highlight=true;
                grid[c][d].setColor(color(white)); 
              }
              else
                break;
            }
          }
        } // for 
        if (donePC) 
          break;
      } // if
    } // for

    // ---

    if (!donePC) { 
      // choose a position via going from left to right
      // simulate move of the opponent 
      for (int c=0; c<cols; c++) {
        if (!donePC) {
          for (int d = 0; d<rows; d++) {
            if (!donePC) {
              if ( (grid[c][d].getColor() == color(white) || grid[c][d].getColor() == color(gray)) ) {
                if (d == 5 || (gridChecker[c][d + 1] == 1 || gridChecker[c][d+1] == 2)) {
                  // save 
                  int oldgridChecker = gridChecker[c][d];
                  // make move 
                  grid[c][d].setHighlightOff();
                  grid[c][d].setColor(colorFromPlayer(!humanMustMakeHisMove));
                  gridChecker[c][d] = intFromPlayer(!humanMustMakeHisMove);   // simulate move of the opponent 
                  // win? 
                  if (checkWin() == true) {
                    if (winner==winnerFromPlayer(!humanMustMakeHisMove)) {
                      if (!donePC) {
                        // this is the move - success 
                        donePC = true;
                        winner = 0;
                        count++;
                        gridChecker[c][d] = intFromPlayer( humanMustMakeHisMove );  // set move to PC move 
                        grid[c][d].setColor(colorFromPlayer( humanMustMakeHisMove ));
                        println ("AI winning move found for opponent. " + humanMustMakeHisMove);
                      } // if
                    } // if
                  } // if
                  if (!donePC) {
                    // restore 
                    gridChecker[c][d] = oldgridChecker;
                    grid[c][d].highlight=true;
                    grid[c][d].setColor(color(white));
                  }
                } // if
              } // if
            } // if
          } // for
        } // if
      } // for
    } // if 

    if (!donePC) {
      // search a pattern of 2   - offensive action 
      if (intFromPlayer( humanMustMakeHisMove ) == 1) {
        // reds move    
        donePC=checkPattern(2, 0, 2);
      }
      else 
      {
        // blacks move    
        donePC=checkPattern(0, 2, 2);
      }
      if (donePC) {
        println ("Pattern");
      } // if
    } // if 

    if (!donePC) {
      // search a pattern of 1      - offensive action 
      if (intFromPlayer( humanMustMakeHisMove ) == 1) {
        // reds move    
        donePC=checkPattern(1, 0, 3);
      }
      else 
      {
        // blacks move    
        donePC=checkPattern(0, 1, 3);
      }
      if (donePC) {
        println ("Pattern");
      } // if
    } // if 

    if (!donePC) {
      // search a pattern of 2   - defensive action 
      if (intFromPlayer( humanMustMakeHisMove ) == 1) {
        // reds move: block opponent (yellow) when he has 2    
        donePC=checkPattern(0, 2, 2);
      }
      else 
      {
        // yellow move: block opponent (red) when he has 2        
        donePC=checkPattern(2, 0, 2);
      }
      if (donePC) {
        println ("Pattern");
      } // if
    } // if 

    if (!donePC) {
      // search a pattern of 1    - defensive action 
      if (intFromPlayer( humanMustMakeHisMove ) == 1) {
        // reds move: block opponent (yellow) when he has 1
        donePC=checkPattern(0, 1, 3);
      }
      else 
      {
        // yellow move: block opponent (red) when he has 1      
        donePC=checkPattern(1, 0, 3 );
      }
      if (donePC) {
        println ("Pattern");
      } // if
    } // if 

    // the last possibility: random 
    if (!donePC) {
      updatePCMoveForHumanVersusPC_Random();
    } // if
    humanMustMakeHisMove = true;
  } // if
} // func 

// -----------------------------------------------------------------------

boolean checkPattern(int findRed, int findYellow, int findEmpty)
{
  // A powerful function that checks 4 cells next to each other and
  // when a given pattern is matched sets any empty cell within the row. 
  // A pattern is a combination like 2 red, 0 yellow and 2 empty cells.
  // The order of the cells is not defined. 
  // Which empty cell is chosen is also not said.
  //  
  // For this function the sum must be 4 (he checks only 4 cells). 
  //
  if ((findRed + findYellow + findEmpty) != 4) // boolean checkPattern is not sum of 4
    exit(); // code error
  //
  CountPieces counter = new CountPieces ();  // int findRed, int findYellow, int findEmpty
  //
  //horizontal
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols-3; j++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(j, i);
      counter.countField(j+1, i);
      counter.countField(j+2, i);
      counter.countField(j+3, i);
      // does pattern match ?
      if (counter.red==findRed && counter.yellow == findYellow && counter.empty == findEmpty) {
        // has an empty field been found? 
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            println("make move horizontal");
            return true;
          }
        }
      }
    }
  }

  //vertical
  for (int i = 0; i < rows-3; i++) {
    for (int j = 0; j < cols; j++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(j, i) ;
      counter.countField(j, i+1) ;
      counter.countField(j, i+2) ;
      counter.countField(j, i+3) ;
      // does pattern match ?
      if (counter.red == findRed && counter.yellow == findYellow && counter.empty == findEmpty) {
        // has an empty field been found?
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            println("make move vertical");
            return true;
          }
        }
      }
    }
  }
  // diagonals
  for (int i = 0; i < rows-3; i++) {
    for (int j = 0; j < cols-3; j++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(j, i) ;
      counter.countField(j+1, i+1) ;
      counter.countField(j+2, i+2) ;
      counter.countField(j+3, i+3) ;
      // does pattern match ?
      if (counter.red == findRed && counter.yellow == findYellow && counter.empty == findEmpty) {
        // has an empty field been found?
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            println("make move vertical");
            return true;
          }
        }
      }
    }
  }

  for (int i = 0; i < rows-3; i++) {
    for (int j = 3; j < cols; j++) {
      counter = new CountPieces ();
      // count the cell types  
      counter.foundEmptyField.x=-1;
      counter.countField(j, i) ;
      counter.countField(j-1, i+1) ;
      counter.countField(j-2, i+2) ;
      counter.countField(j-3, i+3) ;
      // does pattern match ?
      if (counter.red == findRed && counter.yellow == findYellow && counter.empty == findEmpty) { 
        // has an empty field been found?
        if (counter.foundEmptyField.x!=-1) {
          if (makeMove(int(counter.foundEmptyField.x), int(counter.foundEmptyField.y))) {
            println("make move vertical");
            return true;
          }
        }
      }
    }
  }
  return false;
}

boolean makeMove (int i, int j ) {
  boolean doneMakeMove = false;  
  for (int x = 0; x<rows; x++) {
    if ( (grid[i][x].getColor() == color(white) || grid[i][x].getColor() == color(gray)) ){
      if (x == 5 || (gridChecker[i][x + 1] == 1 || gridChecker[i][x+1] == 2)) {
        if (j == x) {
          grid[i][j].setHighlightOff();
          count++;
          grid[i][j].setColor(colorFromPlayer(humanMustMakeHisMove));
          gridChecker[i][j] = intFromPlayer(humanMustMakeHisMove);
          doneMakeMove = true;
        }
      }
    }
  }
  return doneMakeMove;
}

// minor tools: these tools evaluate humanMustMakeHisMove in different ways
color colorFromPlayer(boolean humanMustMakeHisMove)
{
  // the color a red or yellow cell has
  if (humanMustMakeHisMove) 
    return color(red); 
  else 
    return color(yellow); 
}

int intFromPlayer(boolean humanMustMakeHisMove) 
{
  // the value a red or yellow cell has
  if (humanMustMakeHisMove) 
    return 1; // 1 
  else 
    return 2; // 2
}

String stringFromPlayer(boolean humanMustMakeHisMove) 
{
  // text of the player
  if (humanMustMakeHisMove) 
    return "red";   //  1 
  else 
    return "yellow"; // 2
}

int winnerFromPlayer(boolean humanMustMakeHisMove) 
{
  // the count for detecting a win 
  if (humanMustMakeHisMove) 
    return 4;   // red
  else 
    return 8;   // yellow
}

// =======================================================================

class CountPieces 
{
  int red = 0;
  int yellow = 0;
  int empty = 0;
  PVector foundEmptyField = new PVector(-1, -1, 0);
  //
  void display() 
  {
    println ( "count: " + red + " - " + yellow + " - " + empty ) ;
  } 

  PVector countField (int i, int j)
  {
    int gridCell = gridChecker[i][j] ;
    switch (gridCell)
    {
    case 1: 
      red++; 
      break;
    case 2: 
      yellow++; 
      break;
    case 10: 
      empty++;
      foundEmptyField.x = i;
      foundEmptyField.y = j;
      break;
    default: 
      exit(); 
      break;
    } // switch
    return foundEmptyField;
  } // func 
} // class 

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

  void setHighlightOff()
  {
    highlight = false;
  }
  
   boolean over()
  {
    if (overCircle(x, y, size)) 
    {
      over = true;
      return true;
    }
    else 
    {
      over = false;
      return false;
    }
  }
  
  void update()
  {
    if(over() && highlight)
    {
      currentcolor = highlightcolor;
    }
    else if (currentcolor == highlightcolor && !over()) 
    {
      currentcolor = color(white);
    }
  }

  boolean pressed()
  {
    if (over) 
    {
      locked = true;
      return true;
    }
    else 
    {
      locked = false;
      return false;
    }
  }

  boolean overCircle(int x, int y, int diameter)
  {
    float disX = x - mouseX;
    float disY = y - mouseY;
    if (sqrt(sq(disX) + sq(disY)) < diameter/2 )
      return true;
    else 
      return false;
  }

  void setColor(color a) 
  {
    currentcolor = a;
    moveCount = count;
  }

  color getColor()
  {
    return currentcolor;
  }

  void display()
  {
    stroke(currentcolor);
    fill(currentcolor);
    ellipse(x, y, size, size);
    if (showCountMove) {
      if (currentcolor == color(red) || currentcolor == color(yellow)) {
      } // if
    } // if
  } // method */
} // class 
