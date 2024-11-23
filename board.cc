#include "link.h"
#include "cell.h"
#include "board.h"
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

Board::Board(int width, int height) {
    //resize board to have height rows
    board.resize(height);

    for (int i = 0; i < height; ++i) {
        //resize every row to have width cols
        board[i].resize(width);
        //allocate unique_ptr<Cell> for each cell
        for (int j = 0; j < width; ++j) {
            bool isServer = ((i == 0 && (j == 3 || j == 4)) || 
                              (i == (height - 1) && (j == 3 || j == 4)));
            board[i][j] = std::make_unique<Cell>(i, j, isServer);
        }
    }
}

char Board::charAt(int row, int col) const{
    return board[row][col]->getState();
}

Cell* Board::getCell(int row, int col) {
    return board[row][col].get(); //returns a raw ptr
}

/*
int main() {
    unique_ptr<Board> b1 = make_unique<Board>(8, 8);
    cout << "Should be a .: " << b1->charAt(0,0) << endl;
    cout << "Should be a S: " << b1->charAt(0,4) << endl;
    cout << "Should be a S: " << b1->charAt(7,3) << endl;
    cout << "Should be a .: " << b1->charAt(4,3) << endl;
    b1->getCell(0,3)->isServer() ? cout << "Server" << endl: cout << "Not server" << endl;
    b1->getCell(0,5)->isServer() ? cout << "Server" << endl: cout << "Not server" << endl;
    b1->getCell(6,6)->isServer() ? cout << "Server" << endl: cout << "Not server" << endl;
    b1->getCell(2,3)->isFirewall(1) ? cout << "Firewall" << endl: cout << "Not firewall" << endl;
    b1->getCell(2,3)->toggleFirewall(1);
    b1->getCell(2,3)->isFirewall(1) ? cout << "Firewall" << endl: cout << "Not firewall" << endl;
}
*/
