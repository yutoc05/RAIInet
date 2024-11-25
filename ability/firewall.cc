#include "ability.h"
#include "firewall.h"
#include "../board.h"
#include "../player.h"
#include "../game.h"

Firewall::Firewall(): Ability("Firewall", move(theGame)) {}

Firewall::~Firewall() {
}

void Firewall::activate(Player& player, Player& opponent) {
    int row, col;

    while (true) {
        cin >> row;
        cin >> col;

        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            throw logic_error ("Coordinates are outside the board's dimensions.");
        }

        Cell* selectedCell = player.getGame()->theBoard()->getCell(row, col);
        // Board& gameBoard = Board::getInstance();
        // Cell* selectedCell = gameBoard.getCell(row, col);
        if (selectedCell && selectedCell->getState() == '.') {
            char firewallSymbol = player.getGame()->getTurn() == 1 ? 'm' : 'w';
            setUsed(true);
            selectedCell->setState(firewallSymbol); // This will notify TextDisplay to update
            cout << "Firewall " << firewallSymbol << " has been set at (" 
                << col << ", " << row << ")" << endl;
            cout << *player.getGame()->theBoard();

            // define whose firewall it is for the cell
            if (player.getGame()->getTurn() == 1) selectedCell->toggleFirewall(1);
            else selectedCell->toggleFirewall(2);
            
            break;

        } else {
            throw logic_error {"Cannot place a firewall on an occupied square."};
        }

    }

    
}

// Board& Scan::getGameBoard() {
//     return Board::getInstance();
// }


