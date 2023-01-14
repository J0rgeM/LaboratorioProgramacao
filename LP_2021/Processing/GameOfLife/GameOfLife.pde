int rows = 40;
int columns = 50;
int cellSize = 10;

final int windowWidth = columns * cellSize;
final int windowHeight = rows * cellSize;

// Variables for timer
int interval = 100;
int lastRecordedTime = 0;

// Colors for active/inactive cells
final color alive = color(0, 200, 0);
final color dead = color(0);
final color black = color(0);

// Array of cells
int[][] cells; 
// Buffer to record the state of the cells and use this while changing the others in the interations
int[][] cellsBuffer; 

// Pause
boolean pause = true;

void settings()
{
  size(windowWidth, windowHeight);
  noSmooth();
}

void setup() 
{
  // Instantiate arrays 
  cells = new int[rows][columns];
  cellsBuffer = new int[rows][columns];
  // This stroke will draw the background grid
  stroke(48);
}

void DrawGrid()
{
  //Draw grid
  for (int i=0; i<rows; i++) {
    for (int j=0; j<columns; j++) {
      if (cells[i][j]==1) {
        fill(alive); // If alive
      }
      else {
        fill(dead); // If dead
      }
      rect(j*cellSize, i*cellSize, cellSize, cellSize);
    }
  }
}

void iteration() { // When the clock ticks
  // Save cells to buffer (so we opeate with one array keeping the other intact)
  for (int i=0; i<rows; i++) {
    for (int j=0; j<columns; j++) {
      cellsBuffer[i][j] = cells[i][j];
    }
  }

  // Visit each cell:
  for (int i=0; i<rows; i++) {
    for (int j=0; j<columns; j++) {
      // And visit all the neighbours of each cell
      int neighbours = 0; // We'll count the neighbours
      for (int ii=i-1; ii<=i+1;ii++) {
        for (int jj=j-1; jj<=j+1;jj++) {  
          if (((ii>=0)&&(ii<rows))&&((jj>=0)&&(jj<columns))) { // Make sure you are not out of bounds
            if (!((ii==i)&&(jj==j))) { // Make sure to to check against self
              if (cellsBuffer[ii][jj]==1){
                neighbours ++; // Check alive neighbours and count them
              }
            } // End of if
          } // End of if
        } // End of yy loop
      } //End of xx loop
      // We've checked the neigbours: apply rules!
      if (cellsBuffer[i][j]==1) { // The cell is alive: kill it if necessary
        if (neighbours < 2 || neighbours > 3) {
          cells[i][j] = 0; // Die unless it has 2 or 3 neighbours
        }
      } 
      else { // The cell is dead: make it live if necessary      
        if (neighbours == 3 ) {
          cells[i][j] = 1; // Only if it has 3 neighbours
        }
      } // End of if
    } // End of y loop
  } // End of x loop
} // End of function

void Timer()
{
  // Iterate if timer ticks
  if (millis()-lastRecordedTime>interval) {
    if (!pause) {
      iteration();
      lastRecordedTime = millis();
    }
  }
}

void CreateCells()
{
  // Create  new cells manually on pause
  if (mousePressed) {
    int xCellOver = mouseX / cellSize;
    int yCellOver = mouseY / cellSize;
     cells[yCellOver][xCellOver]= 1-cells[yCellOver][xCellOver]; 
    } 
  else if (!mousePressed) { // And then save to buffer once mouse goes up
    // Save cells to buffer (so we opeate with one array keeping the other intact)
    for (int x=0; x<rows; x++) {
      for (int y=0; y<columns; y++) {
        cellsBuffer[x][y] = cells[x][y];
      }
    }
  }
}

void keyPressed() {
  if (key=='r' || key == 'R') {
      pause = !pause;
     }
  
  if (key==' ') { // On/off of pause
    pause = !pause;
  }
  if (key=='c' || key == 'C') { // Clear all
    for (int x=0; x<rows; x++) {
      for (int y=0; y<columns; y++) {
        cells[x][y] = 0; // Save all to zero
      }
    }
  }
  }

void draw()
{
  DrawGrid();
  Timer();
  CreateCells();
}
