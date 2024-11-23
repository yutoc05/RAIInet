#include "blackhole.h"
#include "../board.h"
#include "../player.h"
#include "../game.h"

Blackhole::Blackhole() : Ability("Blackhole", move(theGame)) {}

Blackhole::~Blackhole() {}

void Blackhole::activate(Player& player, Player& opponent) {
    int row, col;

    while (true) {
        std::cout << "Enter the coordinates to place a Blackhole (row col): ";
        std::cin >> row >> col;

        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            std::cerr << "Coordinates are outside the board's dimensions." << std::endl;
            continue;
        }

        Cell* selectedCell = player.getGame()->getBoard()->getCell(row, col);
        if (selectedCell && selectedCell->getState() == '.') {
            setUsed(true);
            selectedCell->setState(' '); // Invisible to the opponent
            selectedCell->toggleBlackhole(true); // Mark the cell as a Blackhole internally
            std::cout << "Blackhole has been placed at (" << col << ", " << row << ")." << std::endl;
            break;
        } else {
            std::cerr << "Cannot place a Blackhole on an occupied square." << std::endl;
        }
    }
}

