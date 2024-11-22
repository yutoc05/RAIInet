#ifndef BOARD_H
#define BOARD_H
#include "link.h"
#include "cell.h"
#include "subject.h"
#include <memory>
#include <vector>
using namespace std;

class Board: public Subject{
    vector<vector<unique_ptr<Cell>>> board;
    public:
    Board(int width, int height);
    char charAt(int row, int col) const override; //zero indexed 
    Cell* getCell(int row, int col);
};

#endif
