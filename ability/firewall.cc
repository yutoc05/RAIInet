#include "ability.h"
#include "firewall.h"
#include "../board.h"
#include "../player.h"
#include "../game.h"
#include <iostream>

Firewall::Firewall(Game*& theGame): Ability("Firewall", theGame) {}

Firewall::~Firewall() {
}

void Firewall::activate(Player& player, Player& opponent) {
    int row, col;

    while (true) {
        cout << "Enter coordinates (row col): ";
        cin >> row >> col;

        // Check if input is valid (within the board's range)
        if (cin.fail()) {
            cin.clear();  // clear the error flag
            cin.ignore(9999, '\n');  // discard the invalid input
            cerr << "Invalid input. Please enter numeric values for row and column.\n";
            continue;
        }

        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            cerr << "Coordinates are outside the board's dimensions. Try again.\n";
            continue;
        }

        // Check if the cell is available for placing a firewall
        Cell* selectedCell = player.getGame()->theBoard()->getCell(row, col);
        if (selectedCell && selectedCell->getState() == '.') {
            char firewallSymbol = (player.getGame()->getTurn() == 1) ? 'm' : 'w';
            setUsed(true);
            selectedCell->setState(firewallSymbol); // Update the board
            cout << "Firewall " << firewallSymbol << " has been set at (" 
                 << col << ", " << row << ")" << endl;
            cout << *player.getGame()->theBoard();

            // Define whose firewall it is for the cell
            if (player.getGame()->getTurn() == 1) {
                selectedCell->toggleFirewall(1);
            } else {
                selectedCell->toggleFirewall(2);
            }

            break;  // Exit the loop once the firewall is successfully placed
        } else {
            cerr << "Cannot place a firewall on an occupied square. Try again.\n";
        }
    }
    setUsed(true);
}


// Board& Scan::getGameBoard() {
//     return Board::getInstance();
// }


