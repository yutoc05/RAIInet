#include "ability.h"
#include "../player.h"
#include "polarize.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Player;

Polarize::Polarize() : Ability("Polarize", move(theGame)) {
      // Constructor for Polarize
}

Polarize::~Polarize(){}

void Polarize::activate(Player& player, Player& opponent) { 
    string linkName;

    while (true) {
        cin >> linkName;

        // Get the link from the player
        Link& link = opponent.getLink(linkName[0]);
        if (islower(linkName[0])) link = player.getLink(linkName[0]);

        // if the link id does not exist
        if (!(linkName == "a" || linkName == "b" || linkName == "c" || linkName == "d" || 
                linkName == "e" || linkName == "f" || linkName == "g" || linkName == "h" || 
                linkName == "A" || linkName == "B" || linkName == "C" || linkName == "D" || 
                linkName == "E" || linkName == "F" || linkName == "G" || linkName == "H")) {
            throw logic_error {"This link id does not exist. Try again."};
        }
        // Check if it's a data link or a virus link 
        else if (link.checkIfData()) {
            link.setIsData(false);
            cout << "Link " << linkName << " has been polarized from a Data to a Virus link." << endl;
            break;  // Exit loop after successful polarization
        } 
        else {
            link.setIsData(true);
            cout << "Link " << linkName << " has been polarized from a Virus to a Data link." << endl;
            break;  // Exit loop after successful polarization
        }
    }
}
