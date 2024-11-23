#include "ability.h"
#include "linkboost.h"

#include "../board.h"
#include "../player.h"
#include "../game.h"


 // Constructor for download
LinkBoost::LinkBoost() : Ability("LinkBoost", move(theGame)) {
}

//create destructor
LinkBoost::~LinkBoost() {
}

//create activate

void LinkBoost::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to polarize 
    // cout << "ID of the link you want to boost: ";
    char id;

    while (true) {
        cin >> id;
        //get the link we want to work with
        Link& link = player.getLink(id);

        // Check if the link is boosted
        if (link.checkIfBoosted()) {
            cout << "Link " << id << " has already been boosted. Please re-enter the link id: ";
        } else {
            link.setIsBoosted(true);
            cout << "Link " << id << " has been boosted." << endl;
            setUsed(true);
            break; 
        }
    }
}








