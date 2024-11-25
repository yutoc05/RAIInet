#ifndef __BLACKHOLE_H__
#define __BLACKHOLE_H__

#include <iostream>
#include <string>
#include "ability.h"


class Blackhole : public Ability {
public:
    Blackhole();
    ~Blackhole();
    void activate(Player& player, Player& opponent) override; // Activates the ability
};

#endif

