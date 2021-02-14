#include<stdio.h>
#include <vector>
#include <string>
#include <iostream>

class Cell {
    private:
        int value; //The value contained within this cell, 0 for unassigned

        unsigned int possibleValues = 511; //The set of possible values for this cell

    public:
        //Positions in the parent groups, Row : 0, Column : 1, Block : 2 
        int groupId[3];

        void Cell() {
            value = 0;
        }

        void Cell(cellValue) {
            value = cellValue;
        }

        void setValue(int cellValue) {
            value = cellValue;
        }

        int getValue(){
            return value;
        }

        void blockValue(int blockValue) {
            //Set the corresponding bit to zero
            possibleValues &= ~(1<<(blockValue-1)); 
        }

        std::vector<int> *getPossibleValues() {
            std::vector<int>* possible = new std::vector<int>();

            for (int i = 0; i < 9; i++){
                if (1<<i && possibleValues){
                    (*possible).push_back(i);
                }
            }

            return possible;
        }

        void printValues() {
            if (value){
                std::cout << std::printf("Cell in GroupID [%d, %d, %d] has value: %d",
                    groupId[0], groupId[1], groupId[2], getValue()) << std::endl;
            }
            else{
                std::cout << std::printf("Cell in GroupID [%d, %d, %d] has values:",
                     groupId[0], groupId[1], groupId[2]) << std::endl;

                for (int v : *(this->getPossibleValues())) {
                    std::cout << v << ' ';
                }
                std::cout << std::endl;
            }
        }

};
