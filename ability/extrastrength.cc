#include "ability.h"
#include "extrastrength.h"

#include "../board.h"
#include "../player.h"
#include "../game.h"

//create constructor
ExtraStrength::ExtraStrength(): Ability("ExtraStrength", move(theGame)) {}

//create destructor
ExtraStrength::~ExtraStrength() {}

//create activate
void ExtraStrength::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to boost strength 
    //cout << "Enter the ID of the link you want to move: ";
    char id;
     while (true) {
        cin >> id;

        Link *l; // pointer to the link we strengthening
        if (player.getGame()->getTurn() == 1 && (id == 'a' || id == 'b' || id == 'c' || id == 'd' ||
                id == 'e' || id == 'f' || id == 'g' || id == 'h')) {
            l = &player.getPureLink(id);
        }
        else if (player.getGame()->getTurn() == 2 && (id == 'A' || id == 'B' || id == 'C' || 
            id == 'D' || id == 'E' || id == 'F' || id == 'G' || id == 'H')) {
            l = &player.getPureLink(id);
        }
        else throw logic_error {"Invalid Id. Try again."};

        l->setStrength(l->getStrength() + 1);
        setUsed(true);
        cout << "Link " << id << " has had extra strength added.\n";
        break; // Exit the loop since we found the link
    }
}







