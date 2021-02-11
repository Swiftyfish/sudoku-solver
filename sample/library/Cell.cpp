#include<stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include<fmt/core.h>

class Cell {
    private:
        int value; //The value contained within this cell, 0 for unassigned
        unsigned int possibleValues = 256; //The set of possible values for this cell

    public:
        int position; //The position of the cell within the group, labelled left to right
        int[3] groupId; //Positions in the parent groups, Row : 0, Column : 1, Block : 2 

        void setValue(int cellValue) {
            value = cellValue;
        }

        int getValue(){
            return value;
        }

        void blockValue(int blockValue) {
            possibleValues &= ~(1<<(blockValue-1)); //Set the corresponding bit to zero
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
                std::printf("Cell at position %d in GroupID [%d, %d, %d] has value: %d",
                    position, groupId[0], groupId[1], groupId[2], getValue()) << endl;
            }
            else{
                std::printf("Cell at position %d in GroupID [%d, %d, %d] has values:",
                    position, groupId[0], groupId[1], groupId[2]) << endl;

                for (int v : *(this->getPossibleValues())) {
                    std::cout << v << ' ';
                }
                std::cout << endl;
            }
        }

};