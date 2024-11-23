#ifndef _POLARIZE_H_
#define _POLARIZE_H_
#include <iostream>
#include <string>
#include "ability.h"

using namespace std;
class Ability;

class Polarize : public Ability {
    // put private fields/methods here if needed
    
    public:
    Polarize();
    ~Polarize();
     void activate(Player& player, Player& opponent )  override; // reads input and activates ability
};

#endif
