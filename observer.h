#ifndef OBSERVER_H
#define OBSERVER_H

class Cell; // not sure why Cell needs to be forward declared here

class Observer {
   public:
    virtual void notify() = 0; // Notify method that must be overwritten by concrete observers
    //c is the cell that call notify
    virtual ~Observer() = default;
    //virtual void notify(Cell& c) = 0;
};

#endif
