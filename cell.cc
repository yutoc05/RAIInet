#include "cell.h"
#include "link.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

Cell::Cell(): row{-1}, col{-1}, state{'.'} {}

/*
Cell::Cell(int row, int col, bool server): row{row}, col{col}, 
        state{'.'}, server{server} {
    if (server) {
        state = 'S';
    }
}
*/

void Cell::setCoords(int r, int c) {
    r = row;
    c = col;
}

void Cell::setState(char c) {
    state = c;
}

char Cell::getState() const{
    return state;
}

void Cell::addLink(unique_ptr<Link> l) {
    l->setPosX(col);
    l->setPosY(row);
    state = l->getSymbol();
    link = move(l);
}

unique_ptr<Link> Cell::detachLink() {
    return move(link);
}

bool Cell::hasLink() {
    if (link) { //link is not nullptr
        return true;
    }
    return false;
}

Link* Cell::getLink() {
    return link.get();
}

bool Cell::isServer() const{
    return (state == 'S');
}

void Cell::toggleFirewall(int player) {
    if (player == 1 && !player1Firewall) { //let player 1 be true, player 2 be false
        player1Firewall = true;
    } else if (player == 1) {
        player1Firewall = false;
    } else if (player == 2 && !player2Firewall) {
        player2Firewall = true;
    } else {
        player2Firewall = false;
    }
}

bool Cell::isFirewall(int player) const{
    //returns whether the player has a firewall in this cell
    if (player == 1) {
        return player1Firewall;
    }
    return player2Firewall;
}

void Cell::toggleBlackhole(int player) {
    if (player == 1 && !player1Blackhole) { //let player 1 be true, player 2 be false
        player1Blackhole = true;
    } else if (player == 1) {
        player1Blackhole = false;
    } else if (player == 2 && !player2Blackhole) {
        player2Blackhole = true;
    } else {
        player2Blackhole = false;
    }
}

bool Cell::isBlackhole(int player) const{ 
    //returns whether the player has a blackhole in this cell
    //let player 1 be true, player 2 be false
    if (player == 1) {
        return player1Blackhole;
    } else {
        return player2Blackhole;
    }
}

/*
void Cell::attachObserver(Observer *o) {
    observers.push_back(o);
}


void Cell::notifyObservers() {
    for (Observer* o : observers) {
        o->notify();
    }
}
*/

/* Tested works as expected - RT Nov. 21
int main() {
    unique_ptr<Cell> c1 = make_unique<Cell>(1, 2, false);
    unique_ptr<Link> l1 = make_unique<Link>(0, 0, 3);
    // add/detach link
    c1->hasLink() ? cout << "Has link" << endl : cout << "No link" << endl;
    c1->addLink(move(l1));
    c1->hasLink() ? cout << "Has link" << endl : cout << "No link" << endl;
    c1->detachLink();
    c1->hasLink() ? cout << "Has link" << endl : cout << "No link" << endl;

    // server check
    c1->isServer() ? cout << "Server" << endl : cout << "Not a server" << endl;
    unique_ptr<Cell> c2 = make_unique<Cell>(1, 2, true);
    c2->isServer() ? cout << "Server" << endl : cout << "Not a server" << endl;

    //Firewall check
    c1->isFirewall(1) ? cout << "Firewall" << endl : cout << "Not a firewall" << endl;
    c1->toggleFirewall(2);
    c1->isFirewall(1) ? cout << "Firewall" << endl : cout << "Not a firewall" << endl;
    c1->toggleFirewall(1);
    c1->isFirewall(1) ? cout << "Firewall" << endl : cout << "Not a firewall" << endl;
    c1->toggleFirewall(1);
    c1->isFirewall(1) ? cout << "Firewall" << endl : cout << "Not a firewall" << endl;

    //Trap check
    c1->isTrap(1) ? cout << "Trap" << endl : cout << "Not a trap" << endl;
    c1->toggleTrap(2);
    c1->isTrap(1) ? cout << "Trap" << endl : cout << "Not a trap" << endl;
    c1->toggleTrap(1);
    c1->isTrap(1) ? cout << "Trap" << endl : cout << "Not a trap" << endl;
    c1->toggleTrap(1);
    c1->isTrap(1) ? cout << "Trap" << endl : cout << "Not a trap" << endl;

    //Blackhole check
    c1->isBlackhole(1) ? cout << "Blackhole" << endl : cout << "Not a Blackhole" << endl;
    c1->toggleBlackhole(2);
    c1->isBlackhole(1) ? cout << "Blackhole" << endl : cout << "Not a Blackhole" << endl;
    c1->toggleBlackhole(1);
    c1->isBlackhole(1) ? cout << "Blackhole" << endl : cout << "Not a Blackhole" << endl;
    c1->toggleBlackhole(1);
    c1->isBlackhole(1) ? cout << "Blackhole" << endl : cout << "Not a Blackhole" << endl;
}
*/
