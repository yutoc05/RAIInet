#include "ability.h"
#include "../player.h"
#include "polarize.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Player;

Polarize::Polarize(Game*& theGame) : Ability("Polarize", theGame) {
      // Constructor for Polarize
}

Polarize::~Polarize(){}

void Polarize::activate(Player& player, Player& opponent) {
    char id;

    while (true) {
        cin >> id;

        // Get the link from the player
        Link& link = opponent.getLink(id);
        if (islower(id) && !opponent.linkExists(id)) {
            cin.clear();
            cin.ignore(9999, '\n');
            cerr << "This link id does not exist. Try again." << endl;
            continue;
        } else if (link.getIsData()) {
            link.setIsData(false);
            string newName = "V" + to_string(link.getStrength());
            opponent.setLinkName(id, newName);
            cout << "Link " << id << " has been polarized from a Data to a Virus link." << endl;
            break;  // Exit loop after successful polarization
        } else {
            link.setIsData(true);
            string newName = "D" + to_string(link.getStrength());
            opponent.setLinkName(id, newName);
            cout << "Link " << id << " has been polarized from a Virus to a Data link." << endl;
            break;  // Exit loop after successful polarization
        }
    }
    setUsed(true);
}

/*
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
        else if (link.getIsData()) {
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
    setUsed(true);
}
*/
