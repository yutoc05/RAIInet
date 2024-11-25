#ifndef _TEXTOBSERVER_H_
#define _TEXTOBSERVER_H_
#include <iostream>
#include <string>
#include "observer.h"
#include "cell.h"
#include "game.h"
class Game;

class TextObserver : public Observer {
    Game *game;  // Pointer to Game for the observer to track the state
   public:
    TextObserver();
    void addGame(Game* g);
    void notify() override;  // Overridden notify to be called when user inputs command "board"
};

#endif
