#ifndef __CELL_H__
#define __CELL_H__

#include <vector>
#include <string> // Include string explicitly
#include <memory>
#include "observer.h"
#include "link.h"

using namespace std;


class Cell {
    int row, col;
    char state;
    const bool server;
    unique_ptr<Link> link;
    vector<Observer*> observers;
    bool player1Firewall, player2Firewall, player1Trap, player2Trap, player1Blackhole, player2Blackhole;
    public:
    Cell(int row, int col, bool server);
    void setCoords(int r, int c);
    void setState(char state);
    char getState() const;
    void addLink(unique_ptr<Link> link);
    unique_ptr<Link> detachLink();
    bool hasLink();
    Link* getLink();
    bool isServer() const;
    void toggleFirewall(int player);
    bool isFirewall(int player) const;
    void toggleBlackhole(int player);
    bool isBlackhole(int player) const;
    void attachObserver(Observer* o);
    void notifyObservers();
};

#endif
