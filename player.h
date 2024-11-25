#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "link.h"
#include "game.h"
//import each ability
#include "ability/ability.h"
#include "ability/linkboost.h"
#include "ability/firewall.h"
#include "ability/download.h"
#include "ability/polarize.h"
#include "ability/scan.h"
#include "ability/movediagonal.h"
#include "ability/blackhole.h"
#include "ability/extrastrength.h"


using namespace std;

class Game;

class Player {
    map<char,Link> links;
    Game *theGame;
    int numData; // # of downloaded data
    int numVirus; // # of downloaded viruses
    unique_ptr<Ability> abilities[5];
    vector<int> firewalls;
    map<char, string> linkNames;

    public:  
        Player(Game* theGame); // must initialize all links
        ~Player();
        Game *getGame();
        int getNumData() const; // how many downloaded data
        int getNumVirus() const; // how many downloaded virus
        int getNumAbilities() const; //how many number of abilities there are

        void downloadLink(Link& currLink); //increment the number of data/virus downloaded
        Link& getLink(char id); // get link at id (a-h) or (A-H)
        Link& getPureLink(char id); // get link at id (a-h) or (A-H) NO EXCEPTION SAFETY NEEDED
        //bool hasSabotagedLink(); // plays guessing game if one is sabotaged to fix

        void addAbility(char ability); // adds ability 'L', 'S', etc.
        void addLink(char id, string link); // adds link during setup. id is 'a','D', etc.
                                            // link is "V4", "D2", etc.
        void moveLink(char id, char direction, bool isP1Turn); // moves link by id in specified
                                                                // direction. Updates link coords
        void useAbility(int i, Player& Opponent); // uses ability at index i
        void printAbilities(); //print the abilities avaliable
        void removeLink(char id);
        vector<Link> getOwns();
        friend std::ostream &operator << (std::ostream &out, const Player &p);
};

#endif
