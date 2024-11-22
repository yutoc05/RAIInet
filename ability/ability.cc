
#include "../board.h"
#include "../player.h"
#include "../game.h"
#include "ability.h"

using namespace std;

//create constructor
Ability::Ability (const string& name, unique_ptr<Game> theGame) : id{-1}, isUsed{false}, theGame{theGame.get()} {
    abilityName = name;
}
//destructor is pure virtual
Ability::~Ability(){
    
}
//getter for ID
int Ability::getId() const{
    return id;
}

//getter for used - checkUsed()
bool Ability::checkUsed() const {
    return isUsed;
}

//getter for ability string
string Ability::getAbility() const{
    return abilityName;
}


void Ability::setUsed(bool value) {
    isUsed = value;
}
