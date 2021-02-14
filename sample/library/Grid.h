#include <stdio.h>
#include <iostream>
#include <string>
#include <Cell.h>
#include <Group.h>

class Grid {
    //Parent grid which is the entire set of cells and groups
    private:
        //The position that we are currently considering
        //This may not be worth storing as it should be trivial to find
        //by scanning left to right for the first cell marked 0
        int position;

        Group rows[9];

        Group columns[9];

        Group blocks[9];
        
        Cell cells[81];

   public:
        void buildGrid(std::string &grid){
            int[81] gridValues = gridBuilder(grid);

            for (int i = 0; i < 81; i++) {
                int row = i / 9;
                int column = i % 9;
                int block = (row / 3) + 3 * (column / 3);  

                Cell cell = new Cell(gridValues[i]);

                rows[row] = cell;
                columns[column] = cell;
                blocks[block] = cell;
                cells[i] = cell;
            }
        }
        
