#include "textobserver.h"
#include "game.h"
#include <iostream>
#include <string>
using namespace std;

TextObserver::TextObserver() {}

void TextObserver::addGame(Game* g) {
    game = g;
}

void TextObserver::notify() {
    cout << "Player 1:" << endl;
    // cout << playerInfo(1); << endl; // not sure if endl needed
    // cout << "Downloaded: " << /*game-> get # of data downloaded by p1*/ << "D, " << /*game-> get # of viruses downloaded by p1*/ << "V" << endl;
    // cout << "Abilities: " << /*game-> get # of player 1's abilities left to use*/ << endl;

    // must print ? if link is hidden and player 2's turn
    // cout << "a: " << /*game-> link(D or V)+strength*/ << " b: " << /*game-> link(D or V)+strength*/ << " c: " << /*game-> link(D or V)+strength*/ << " d: " << /*game-> link(D or V)+strength*/ << endl;
    // cout << "e: " << /*game-> link(D or V)+strength*/ << " f: " << /*game-> link(D or V)+strength*/ << " g: " << /*game-> link(D or V)+strength*/ << " h: " << /*game-> link(D or V)+strength*/ << endl;
    cout << "========" << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i == 0 || i == 7) && (j == 3 || j == 4)) { // prints "S" on server cells (needed if getState logic does not check for this)
                cout << "S";
            } else {
                game->theBoard()->charAt(i, j);
            }
        }
        cout << endl;
    }
    cout << "========" << endl;
    cout << game->playerInfo(2) << endl; // not sure if endl needed
    // cout << "Player 2:" << endl;
    // cout << "Downloaded: " << /*game-> get # of data downloaded by p2*/ << "D, " << /*game-> get # of viruses downloaded by p2*/ << "V" << endl;
    // cout << "Abilities: " << /*game-> get # of player 2's abilities left to use*/ << endl;

    // must print ? if link is hidden and player 1's turn
    // cout << "A: " << /*game-> link(D or V)+strength*/ << " B: " << /*game-> link(D or V)+strength*/ << " C: " << /*game-> link(D or V)+strength*/ << " D: " << /*game-> link(D or V)+strength*/ << endl;
    // cout << "E: " << /*game-> link(D or V)+strength*/ << " F: " << /*game-> link(D or V)+strength*/ << " G: " << /*game-> link(D or V)+strength*/ << " H: " << /*game-> link(D or V)+strength*/ << endl;
}

/*
void TextObserver::notify(Cell& c) {
    // Update a specific cell
    theDisplay[c.getRow()][c.getCol()] = c.getState();
}


std::ostream& operator<<(std::ostream& out, const TextObserver& to) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            out << to.theDisplay[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}
*/
