#include <stdio.h>
#include <Cell.h>

class Group {
    private:
       *Cell[9] cells;
 
    public:
        int position;
        int groupId;

        void updateCells(value, position) {
            //Add the value to position
            //and block the value in all other cells
            for (*Cell cell : cells) {
               if (position) {
                  if (cell->position == position) {
                     cell->setValue(value);
                  }
               }
               else{
                  cell->blockValue(value);
               }
            } 
        }        
}
