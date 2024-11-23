#ifndef _LINKBOOST_H_
#define _LINKBOOST_H_
#include "ability.h"
#include <iostream>
#include <string>

using namespace std;
class Ability;

class Player;
class Game;

class LinkBoost : public Ability {
    // put private fields/methods here if needed
    
    public:
    LinkBoost();
    ~LinkBoost();
    void activate(Player& player, Player& opponent) override; // reads input and activates ability
};


#endif