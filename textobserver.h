#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"

class Game;

class TextObserver : public Observer {
    Game *game;  // Pointer to Game for the observer to track the state
   public:
    TextObserver(Game* game);
    void notify() override;  // Overridden notify to be called when user inputs command "board"
};

#endif
