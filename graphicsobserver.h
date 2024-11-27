#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "observer.h"

class Game;
class Xwindow;

class GraphicsObserver : public Observer {
    Game *game;  // Pointer to Game for the observer to track the state
    Xwindow *window;
    int getColor(int i, int j);
   public:
    GraphicsObserver();
    void addGame(Game* g);
    void notify() override;  // Overridden notify to be called when user inputs command "board"
    //void notify(Cell& c) override;  // Cell-specific updates
    //friend std::ostream& operator<<(std::ostream& out, const TextObserver& to);
};

#endif
