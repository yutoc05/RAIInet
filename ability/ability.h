#ifndef _ABILITY_H_
#define _ABILITY_H_

#include <iostream>
#include <string>
#include <memory>

// #include "../player.h"
// #include "../game.h"

using namespace std;

class Player;
class Game;

/* 
Abilities:
- L: Link Boost
- F: Firewall
- D: Download
- P: Polarize
- S: Scan
- O: Move Link
- A: Sabotage
- T: Strength Boost
*/

class Ability {
    int id;              // the id of the ability
    bool isUsed = false; // has the ability been used yet?
    string abilityName;  // the name of the ability: Move Link, Sabotage, etc.
    protected:
        void setUsed(bool value);
        unique_ptr<Game> theGame;
    public:
        Ability(const string& name, unique_ptr<Game> theGame); // ctor, might need fields for initialization
        //virtual ~Ability() = 0;
        ~Ability();
        virtual void activate(Player& player, Player& opponent) = 0; // pure virtual function
        int getId() const;                 // returns the id of the ability
        bool checkUsed() const;            // returns whether the ability has been used
        string getAbility() const;           // returns the ability name
        
        
};

#endif
