//needs an adaptation of new command, move a down right, etc.

#include "movediagonal.h"
#include "../player.h"
#include "../link.h"

MoveDiagonal::MoveDiagonal(Game*& theGame) : Ability("Move Diagonal", theGame) {}

MoveDiagonal::~MoveDiagonal() {}

void MoveDiagonal::activate(Player& player, Player& opponent) {
    char linkId;
    //std::cout << "Enter the ID of the link to enable diagonal movement: ";
    std::cin >> linkId;

    try {
        Link& link = player.getLink(linkId);
        link.setIsDiagonal(true); // Enable diagonal movement for the selected link
        setUsed(true);
        std::cout << "Link " << linkId << " can now move diagonally!" << std::endl;
    } catch (std::logic_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


