#include "ability.h"
#include "scan.h"
#include "../board.h" 
#include <iostream>
#include <string>

Scan::Scan() : Ability("Scan", move(theGame)) {
    // Constructor for Scan
}

Scan::~Scan() {
    // Destructor for Scan
}

void Scan::activate(Player& player, Player& opponent) {
    char id;

    while (true) {
        cin >> id;

        // Get the link from the player
        Link& link = opponent.getLink(id);
        if (islower(id)) link = player.getLink(id);

        // if the link id does not exist
        else if (!(id == 'a' || id == 'b' || id == 'c' || id == 'd' || 
                id == 'e' || id == 'f' || id == 'g' || id == 'h' || 
                id == 'A' || id == 'B' || id == 'C' || id == 'D' || 
                id == 'E' || id == 'F' || id == 'G' || id == 'H')) {
            throw logic_error {"This link id does not exist. Try again."};
        }
        else {
            link.reveal();
            cout << "Link " << id << " has been revealed." << endl;
            break;  // Exit loop after successful polarization
        }
    }

    // try {
    //     cout << "Enter the coordinates (row and column) to perform the scan: ";
    //     int row, col;
    //     cin >> row >> col;

    //     if (row < 0 || row >= 8 || col < 0 || col >= 8) {
    //         throw std::out_of_range("Coordinates are outside the board's dimensions.");
    //     }

    //     Board& gameBoard = Board::getInstance(); 
    //     Cell* selectedCell = gameBoard.getCell(row, col);

    //     Link* linkInCell = selectedCell->getLink();
    //     if (linkInCell) {
    //         char linkType = linkInCell->checkIfData() ? 'D' : 'V';
    //         int linkStrength = linkInCell->getStrength();

    //         cout << "Scanning reveals a " << linkType << " link with strength " << linkStrength << ".\n";
    //     } else {
    //         cout << "Scanning reveals an empty square.\n";
    //     }
    // } catch (const std::out_of_range& e) {
    //     cout << "Error: " << e.what() << endl;
    // } catch (const std::exception& e) {
    //     // Catch all other standard exceptions
    //     cout << "An unexpected error occurred: " << e.what() << endl;
    // }
}
