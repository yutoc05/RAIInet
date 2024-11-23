//EXAMPLE CODE 


#include "../board.h"
#include "../player.h"
#include "../game.h"
#include "ability.h"

using namespace std;

//create constructor
Ability::Ability (const string& name, unique_ptr<Game> theGame) : type{-1}, isUsed{false}, theGame{theGame.get()} {
    abilityName = name;
}
//destructor is pure virtual
Ability::~Ability(){
    
}
//getter for ID
int Ability::getType) const{
    return type;
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
