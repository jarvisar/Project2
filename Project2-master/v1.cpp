#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

class aliveCells
{
    public:
        
        aliveCells(){
            totalCells = 0;
        }
        
        aliveCells(int n){
            totalCells = n;
        }

        void setAliveCells(int n){
          totalCells = n;
        }
        
        int getNumCells(){
            return totalCells;   
        }
        
        
        
    private:
        int totalCells;
    
};

class Board
{
    public:
        Board(){
            ifstream inputFile;
            inputFile.open("input.txt");
            inputFile >> rows;
            inputFile >> cols;
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
            alive.setAliveCells(k);
            start();
        }
        
        Board(int rows1, int cols1){
            rows = rows1;
            cols = cols1;
            grid = new char* [rows];
            for (int i(0); i < rows; i++){
                grid[i] = new char[cols];
                for (int j(0); j < cols; j++){
                    grid[i][j] = '.';
                }
            }
            alive.setAliveCells(0);
            DisplayBoard(grid);
            CheckLive(grid);
        }

        
        
        void CreateCopy(char **grid){
            copy = new char*[rows];
            for (int i = 0; i < rows; i++){
                copy[i] = new char[cols];
                for (int j = 0; j < cols; j++){
                    copy[i][j] = grid[i][j];
                }
            }
        }

        void addCell(int x, int y){
          grid[x][y] = '*';


        }
        
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
                        
                    alive.setAliveCells(numCells);
                    numCells = 0;
                }
                
            }
            
        }

        void start(){
          do {
            DisplayBoard(grid);
            CheckLive(grid);

          }while(alive.getNumCells() == 0);
        }    
    private:
        int rows;
        int cols;
        char **grid;
        char** copy;
        int numCells;
        aliveCells alive;
        
};


int main()
{
    
    
    

    
    Board gameboard;
    
    

    return 0;
}