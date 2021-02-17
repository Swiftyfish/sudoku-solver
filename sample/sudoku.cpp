#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Takes in the grid from input and stores it in vector form
 *
 * @return The 2D sudoku grid with the same values as the input
 */
vector<vector<int>> processGrid() {
    vector<vector<int>> values(9, vector<int>(9, 0));

    cout << "Input sudoku grid" << endl;

    for (auto &ii : values) {
        for (auto &jj : ii) {
            cin >> jj;
        }
    }

    return values;
}

/**
 * Takes in the grid from input and stores it in vector form
 * @param filepath Path to the sudoku grid as a text file
 *
 * @return The 2D sudoku grid with the same values as the input
 */
vector<vector<int>> processGrid(char *filepath) {
    vector<vector<int>> values(9, vector<int>(9, 0));

    ifstream infile(filepath);

    for (auto &ii : values) {
        for (auto &jj : ii) {
            infile >> jj;
        }
    }

    return values;
}

/**  Prints the current sudoku grid
 *
 * @param grid A reference to the 3x3 sudoku grid
 */ 
void printGrid(vector<vector<int>> &grid) {
    for (vector<int> row : grid) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

/**
 * A progress tracker for the number of iterations
 *
 * @param iterCount  The number of iterations so far
 */
void progressBar(int *iterCount) {
    cout << "Iteration count: " << *iterCount << "\r";
    cout.flush();
}

/**
 * Gets the set of possible values at the position x,y in the grid
 *
 * @param grid The 3x3 sudoku grid
 * @param x    The current row in the grid
 * @param y    The current column in the grid
 *
 * @return     A set of 9 bits indicating which values can be placed at x, y
 *             an active bit i indicates that i+1 can be stored at x, y
*/
int checkGrid(vector<vector<int>> &grid, int x, int y) {
    int possible = 1023;

    // Check the row and column
    for (int i = 0; i < 9; i++) {
        possible &= ~(1<<grid[i][y]);
        possible &= ~(1<<grid[x][i]);
    }

    // Check the block
    int testX = 3 * (x / 3), testY = 3 * (y / 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            possible &= ~(1<<grid[testX + i][testY + j]);
        }
    }

    return possible>>1;
}

/*
 *  Recursive backtracking solver for a 3x3 sudoku
 *
 *  @param grid       The 3x3 grid as a vector of vectors containing the values 
 *  @param x          The current row in the grid
 *  @param y          The current column in the grid
 *  @param iterCount  The current iteration count (number of recursion steps)
 *
 *  @return           A boolean stating whether the grid was solved or not
 */
bool solveStochastic(vector<vector<int>> grid, int x, int y, int* iterCount) {
    *iterCount += 1;
    if (!(*iterCount % 10000)) {
        //cout << "Reached " << *iterCount << " iterations" << endl;
        progressBar(iterCount);
    }
 
    bool check = false;
 
    // Get the set of possible values at x, y
    int possible = checkGrid(grid, x, y);
 
    //cout << "Checking cell " << 9 * x + y << " Possible : " << possible << endl;
 
    if (grid[x][y]){
        // Don't change the value, just move to the next position in the grid
        // and continue solving
 
        if (x == 8 and y == 8) {
            cout << endl << "Finished" << endl;
            printGrid(grid);
            return true;
        }

        if (y == 8){
             check = solveStochastic(grid, x+1, 0, iterCount);
        }
        else{
            check = solveStochastic(grid, x, y+1, iterCount);
        }
    }
    else{
        vector<int> possibleValues;

        //Calculate the possible values and store them in a vector
        for (int i = 0; i < 9; i++) {
            if (possible & (1<<i)) {
                possibleValues.push_back(i+1);
            }
        }

        //Shuffle the vector of possible values
        random_shuffle(possibleValues.begin(), possibleValues.end());

        for (int i : possibleValues){
            //Set the current cell to i
            //cout << "Set Cell " << x << ", " << y << " to " << i << endl;
            grid[x][y] = i;

            if (x == 8 and y == 8) {
                cout << endl << "Finished" << endl;
                printGrid(grid);
                return true;
            }

            if (y == 8){
                check = solveStochastic(grid, x+1, 0, iterCount);
            }
            else{
                check = solveStochastic(grid, x, y+1, iterCount);
            }

            //Reset the current cell
            grid[x][y] = 0;

            if (check) {
                return true;
            }
        }
     }
 
    return check;
}

/*
 *  Recursive backtracking solver for a 3x3 sudoku
 *
 *  @param grid       The 3x3 grid as a vector of vectors containing the values 
 *  @param x          The current row in the grid
 *  @param y          The current column in the grid
 *  @param iterCount  The current iteration count (number of recursion steps)
 *
 *  @return           A boolean stating whether the grid was solved or not
 */
bool solve(vector<vector<int>> grid, int x, int y, int* iterCount) {
    *iterCount += 1;
    if (!(*iterCount % 10000)) {
        //cout << "Reached " << *iterCount << " iterations" << endl;
        progressBar(iterCount);
    }
 
    bool check = false;
 
    // Get the set of possible values at x, y
    int possible = checkGrid(grid, x, y);
 
    //cout << "Checking cell " << 9 * x + y << " Possible : " << possible << endl;
 
    if (grid[x][y]){
        // Don't change the value, just move to the next position in the grid
        // and continue solving
 
        if (x == 8 and y == 8) {
            cout << endl << "Finished" << endl;
            printGrid(grid);
            return true;
        }

        if (y == 8){
             check = solve(grid, x+1, 0, iterCount);
        }
        else{
            check = solve(grid, x, y+1, iterCount);
        }
    }
    else{
        for (int i = 0; i < 9; i++) {
            if (possible & (1<<i)) {
                //Set the current cell to i+1
                //cout << "Set Cell " << x << ", " << y << " to " << i+1 << endl;
                grid[x][y] = i+1;
 
                if (x == 8 and y == 8) {
                    cout << endl << "Finished" << endl;
                    printGrid(grid);
                    return true;
                }

                if (y == 8){
                    check = solve(grid, x+1, 0, iterCount);
                }
                else{
                    check = solve(grid, x, y+1, iterCount);
                }
 
                //Reset the current cell
                grid[x][y] = 0;
            }

            if (check) {
                return true;
            }
        }
     }
 
    return check;
}

int main(int argc, char *argv[]) {
   vector<vector<int>> grid;
       
   //Process optional command line arguments
   if (argc > 1) {
       grid = processGrid(argv[1]);
   }
   else{
       grid = processGrid();
   }
   
   cout << "Grid processed successfully" << endl << endl;

   printGrid(grid);

   cout << endl;

   int iterCount = 0;

   bool check;

   //Start solving grid
   check = solve(grid, 0, 0, &iterCount);
    
   cout << "Solved via brute force method in " << iterCount << " iterations" << endl;

   iterCount = 0;

   check = solveStochastic(grid, 0, 0, &iterCount);
    
   cout << "Solved via stochastic method in " << iterCount << " iterations" << endl;

   return 0; 
}
