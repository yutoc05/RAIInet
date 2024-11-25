#ifndef _BOARD_H_
#define _BOARD_H_
#include "subject.h"
#include "cell.h"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Player;
class TextObserver;


class TextObserver;

class Board: public Subject{
    Cell theBoard[8][8];

    public:
    Board();
    //void init(TextObserver* td);
    char charAt(int row, int col) const override; //zero indexed 
    Cell* getCell(int row, int col);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
