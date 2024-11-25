#include "board.h"
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

Board::Board() {
    // Initialize the board cells
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j]->setCoords(i, j);
        }
    }
}

void Board::init(TextObserver* td) {
    // Attach the TextDisplay observer to every Cell on theBoard
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j]->attachObserver(td); // Attach the observer to the cell
        }
    }
}

char Board::charAt(int row, int col) const{
    return board[row][col]->getState();
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
    // Implement the operator<< to display the board as needed
    out << "========" << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Access the cell's state and display it
            out << b.board[i][j]->getState();
        }
        out << std::endl; // Add a newline after each row
    }
    return out << "========" << endl;;
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
