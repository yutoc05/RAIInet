#ifndef _EXTRASTRENGTH_H_
#define _EXTRASTRENGTH_H_
#include <iostream>
#include <string>

using namespace std;
class Ability;

class ExtraStrength : public Ability {
    // put private fields/methods here if needed
    
    public:
    ExtraStrength(Game*& theGame);
    ~ExtraStrength();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};
#endif
