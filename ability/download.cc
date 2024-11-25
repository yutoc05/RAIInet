
#include "ability.h"

#include "../board.h"
#include "../player.h"
#include "download.h"

using namespace std;

 // Constructor for download
Download::Download(Game*& theGame) : Ability("Download", theGame) {}

//create destructor
Download::~Download() {}

//create activate

void Download::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to download 
    char id;

    while (true) {
        cin >> id;
        // Assuming Ability has a virtual getLink function
        Link& link = opponent.getLink(id);

        // Check if it has already been downloaded
        if (link.getIsDownloaded()) {
            cout << "Link " << id << " has already been downloaded. Please re-enter the link name: ";
        } 
        else if ((player.getGame()->getTurn() == 1 && (id == 'a' || id == 'b' || id == 'c' || 
                                                        id == 'd' || id == 'e' || id == 'f' || 
                                                        id == 'g' || id == 'h')) ||
                (player.getGame()->getTurn() == 2 && (id == 'A' || id == 'B' || id == 'C' || 
                                                        id == 'D' || id == 'E' || id == 'F' || 
                                                        id == 'G' || id == 'H'))) {
            throw logic_error {"You must download your opponent's link, not your own. Try again."};
        }
        else {
            // Change link to be downloaded
            link.setIsDownloaded(true);
            setUsed(true);
            player.downloadLink(link);
            
            char replacement; // get replacement for the hole left by the downloaded link
            if (player.getGame()->theBoard()->getCell(link.getPosY(), link.getPosX())->
                isFirewall(1)) replacement = 'm';
            else if (player.getGame()->theBoard()->getCell(link.getPosY(), link.getPosX())->
                isFirewall(2)) replacement = 'w';
            else replacement = '.';

            player.getGame()->theBoard()->getCell(link.getPosY(), link.getPosX())->
                setState(replacement);
            cout << "Link " << id << " has been downloaded." << endl;
            break; // Exit the loop since we found the link
        }
    }
}




