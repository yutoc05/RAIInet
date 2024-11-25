#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "subject.h"
#include "cell.h"
#include "textobserver.h"
using namespace std;

class TextObserver;

class Board: public Subject{
    vector<vector<unique_ptr<Cell>>> board;
    public:
    Board();
    void init(TextObserver* td);
    char charAt(int row, int col) const override; //zero indexed 
    Cell* getCell(int row, int col);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
