#ifndef _OBSERVER_H_
#define _OBSERVER_H_
//#include "studio.h" commented out so I can compile

class Cell;

class Observer {
    public:
    virtual void notify() = 0;
    //c is the cell that call notify
    virtual ~Observer() = default;
};

#endif
