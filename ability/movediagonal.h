#ifndef __MOVEDIAGONAL_H__
#define __MOVEDIAGONAL_H__

#include <iostream>
#include <string>
#include "ability.h"


class MoveDiagonal : public Ability {
public:
    MoveDiagonal(Game*& theGame);
    ~MoveDiagonal();
    void activate(Player& player, Player& opponent) override; // Activates the ability
};

#endif
