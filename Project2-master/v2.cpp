/*
 * Project Title:
 * - Game of Life
 * Description:
 * Creates a grid of cells that live or die based on the number of adjacent cells that are alive
 *
 * Developers:
 * - A Jarvis  - jarvisar@mail.uc.eud
 * - W Dentino - dentinwm@mail.uc.edu
 *
 * Special Instructions: // optional
    Input syntax:
        <rows>
        <columns>
        <max num of generations>
        Cell 1 <x> <y>
        Cell 2 <x> <y>
        ...
        Cell n <x> <y>
        ...
 *
 * Developer comments: // Not optional
 * Developer 1:
 * Implemented classes and input structure
 * Developer 2:
 * Formatting, testing, edits
 */

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

class aliveCells
{
    public:
 
/* Function Name: aliveCells()
 *
 * Function Description:
 * Default constructor for aliveCells class. Sets the number of living cells to 0 if there is no input.
 *
 * Parameters:
 * none
 *
 * return value:
 * none
 */
 aliveCells(){
            totalCells = 0;
        }
    
 /* Function Name: aliveCells()
 *
 * Function Description:
 * Stores the number of living cells around a location on the board
 *
 * Parameters:
 * none
 *
 * return value:
 * none
 */       
        aliveCells(int n){
            totalCells = n;
        }
    
 /* Function Name: setAliveCells()
 *
 * Function Description:
 * Stores a new value for the number of living cells around a location
 *
 * Parameters:
 * none
 *
 * return value:
 * none
 */ 
        void setAliveCells(int n){
          totalCells = n;
        }
        
 /* Function Name: getNumCells()
 *
 * Function Description:
 * returns the number of living cells at a location
 *
 * Parameters:
 * none
 *
 * return value:
 * totalCells
 */ 
        int getNumCells(){
            return totalCells;   
        }
        
        
        
    private:
        int totalCells;
    
};

class Board
{
    public:
    /* Function Name: Board()
    *
    * Function Description:
    * Defualt constructor for Board class. Creates a board based on values for rows, columns, and living cells inported from Input.txt 
    */
        Board(){
            ifstream inputFile;
            inputFile.open("input.txt");
            inputFile >> rows;
            inputFile >> cols;
            inputFile >> maxGen;
            grid = new char* [rows];
            for (int i(0); i < rows; i++){
                grid[i] = new char[cols];
                for (int j(0); j < cols; j++){
                    grid[i][j] = '.';
                }
            }
            int x = 0;
            int y = 0;
            int k = 0;
            while (!inputFile.eof()){
              inputFile >> x >> y;
              addCell(x,y);
              k++;
            }
            
            start();
        }
    
    /* Function Name: Board()
    *
    * Function Description:
    * Constructor for Board class. Creates a board based on input values for rows and columns then asks the user how many living cells should be made at the start of the game. The user inputs the number and locations for each living cell then the game runs for 20 generations.
    * 
    * Perameters:
    * rows1 is how many rows the board should have
    * cols1 is how many columns the board should have
    *
    * Return value:
    * no return value but will display the board for 20 generations
    */    
        Board(int rows1, int cols1){
            int a = 0, cellx, celly;
            rows = rows1;
            cols = cols1;
            maxGen = 20;
            grid = new char* [rows];
            for (int i(0); i < rows; i++){
                grid[i] = new char[cols];
                for (int j(0); j < cols; j++){
                    grid[i][j] = '.';
                }
            }
            
            cout << "How many living cells should be made?" << endl;
            cin >> a;
            for (int k(0); k < a; k++){
                cout << "Input x,y pair for a cell" << endl;
                cin >> cellx >> celly;
                addCell(cellx - 1,celly - 1);
            }
            
            start();
            
        }

    /* Function Name: CreateCopy()
    *
    * Function Description:
    * Creates a copy of the board in its current state to use when changing the status of cells.
    *
    * Perameters:
    * a pointer to a location on the grid
    *
    * Return value:
    * void
    */                  
        void CreateCopy(char **grid){
            copy = new char*[rows];
            for (int i = 0; i < rows; i++){
                copy[i] = new char[cols];
                for (int j = 0; j < cols; j++){
                    copy[i][j] = grid[i][j];
                }
            }
        }
    
    /* Function Name: addCell()
    *
    * Function Description:
    * Adds a new living cell at a location
    *
    * Perameters:
    * x is the column the cell should be in
    * y is the row the cell should be in
    *
    * Return value:
    * void
    */    
        void addCell(int x, int y){
          grid[x][y] = '*';


        }

    /* Function Name: DisplayBoard()
    *
    * Function Description:
    * Prints the board in its current state
    *
    * Perameters:
    * a pointer to a location on the grid
    *
    * Return value:
    * void
    */        
        void DisplayBoard(char **grid){
            cout << endl;
            for (int i = 0; i < rows; i++){
                cout << setw(5);
                for (int j = 0; j < cols; j++){
                    cout << grid[i][j];
                }
                cout << endl;
            }
            
        }
    
    
    /* Function Name: CheckLive()
    *
    * Function Description:
    * Checks the number of living cells adjacent to a location. If the number of living adjacent cells is less than 2 or greater than 3 there will be a dead cell at the location, if the number of adjacent cells is exactly 2 the state of any cell at the location will not change, if the number of adjacent cells is exactly 3 there will be a living cell at the location.
    *
    * Perameters:
    * a pointer to a location on the grid
    *
    * Return value:
    * void
    */            
        void CheckLive(char **grid){
            CreateCopy(grid);
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < rows; j++){
                    if ((j + 1) < cols && (copy[i][j + 1] == '*'))
                        numCells++;
                        
                    if ((j - 1) >= 0 && copy[i][j - 1] == '*' )
                        numCells++;
                        
                    if ((j - 1) >= 0 && (i - 1) >= 0 && copy[i - 1][j - 1] == '*' )
                        numCells++;
                        
                    if ((i - 1) >= 0 && copy[i - 1][j] == '*' )
                        numCells++;
                        
                    if ((i - 1) >= 0 && (j + 1) < cols && copy[i - 1][j + 1] == '*')
                        numCells++;
                        
                    if ((i + 1) < rows && (j - 1) >= 0 && copy[i + 1][j - 1] == '*')
                        numCells++;
                        
                    if ((i + 1) < rows && copy[i + 1][j] == '*')
                        numCells++;
                        
                    if ((i + 1) < rows && (j + 1) < cols && copy[i + 1][j + 1] == '*')
                        numCells++;
                    
                    
                    if ((numCells < 2) || (numCells > 3))
                        grid[i][j] = '.';
                    else if (numCells == 2)
                        grid[i][j] = copy[i][j];
                    else if (numCells == 3)
                        grid[i][j] = '*';
                        
                    
                    numCells = 0;
                }
                
            }
            
        }
    
/* Function Name: countAlive
 *
 * Function Description:
 * Counts the number of living cells on the board
 *
 * Parameters:
 * a pointer to a location on the grid
 *
 * return value:
 * void
 */
        void countAlive(char **grid){
          int count = 0;
          for (int i = 0; i < rows; i++){
            for (int j = 0; j < rows; j++){
              if (grid[i][j] == '*')
                count++;

            }
          }
          alive.setAliveCells(count);

        }

/* Function Name: start()
 *
 * Function Description:
 * Runs initial set up for the game by printing the board in its initial state, checks to see which cells will live or die, and checks to see how many living cells there are then itterates the game for the input number of generations.
 *
 * Parameters:
 * none
 *
 * return value:
 * none
 */
        void start(){
          int i = 0;
          do {
            DisplayBoard(grid);
            CheckLive(grid);
            countAlive(grid);
            //cout << alive.getNumCells();
            i++;
          }while(alive.getNumCells() != 0 && maxGen > i);
        }    
    
    private:
        int rows;
        int cols;
        char **grid;
        char** copy;
        int numCells;
        aliveCells alive;
        int maxGen;
        
};

/* Function Name: playAgain()
 *
 * Function Description:
 * Asks the user if they want to play another round. If the user says yes they are asked to input starting values fot the game, the game is run, then the user is asked to play again or not.
 *
 * Parameters:
 * none
 *
 * return value:
 * none
 */
void playAgain(){
    int x, y;
    char again;
    cout << "Play again? (Y/N)" << endl;
    cin >> again;
    
    if (again == 'Y'){
        cout << "Input new board size (x,y)" << endl;
        cin >> x >> y;
        Board(x,y);
        playAgain();
    }
    else {
        return;
    }
}

int main()
{
    // Board gameboard;
    playAgain();

    return 0;
}
