#include "ability.h"
#include "scan.h"
#include "../player.h"
#include "../board.h" 
#include <iostream>
#include <string>

Scan::Scan(Game*& theGame) : Ability("Scan", theGame) {
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
        if (islower(id) && !opponent.linkExists(id)) {
            cin.clear();
            cin.ignore(9999, '\n');
            cerr << "This link id does not exist. Try again." << endl;
        } else {    
            link.reveal();
            cout << "Link " << id << " has been revealed." << endl;
            break;  // Exit loop after successful polarization
        }
    }
    setUsed(true);
}
