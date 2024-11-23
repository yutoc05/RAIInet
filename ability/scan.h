#ifndef _SCAN_H_
#define _SCAN_H_
#include <iostream>
#include <string>

using namespace std;
class Ability;

class Scan : public Ability {
    // // put private fields/methods here if needed
    // protected:
    // Board& getGameBoard(); 
    
    public:
    Scan();
    ~Scan();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};

#endif