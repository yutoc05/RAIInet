#ifndef __FIREWALL_H__
#define __FIREWALL_H__
#include <iostream>
#include <string>

using namespace std;
class Ability;

class Firewall : public Ability {
    // put private fields/methods here if needed
   // private:
    //Game& game;
    
    public:
    Firewall();
    ~Firewall();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};

#endif
