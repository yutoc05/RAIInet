#ifndef CELL_H
#define CELL_H
#include "link.h"
#include "observer.h"
#include <vector>
#include <memory>

using namespace std;


class Cell {
    const int row, col;
    char state;
    const bool server;
    unique_ptr<Link> link;
    vector<Observer*> observers;
    bool player1Firewall, player2Firewall, player1Trap, player2Trap, player1Blackhole, player2Blackhole;
    
    public:
        Cell(int row, int col, bool server);
        void setState(char state);
        char getState();
        void addLink(unique_ptr<Link> link);
        void detachLink();
        bool hasLink();
        bool isServer() const;
        void toggleFirewall(int player);
        bool isFirewall(int player) const;
        void toggleTrap(int player);
        bool isTrap(int player) const;
        void toggleBlackhole(int player);
        bool isBlackhole(int player) const;
        void attachObserver(Observer* o);
        void notifyObservers();
};

#endif
