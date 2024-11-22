#ifndef SUBJECT_H
#define SUBJECT_H
#include "observer.h"
#include <vector>
#include <memory>
using namespace std;


class Subject {
    std::vector<unique_ptr<Observer>> observers;
    public:
    void attach(unique_ptr<Observer> o);
    void detach(Observer* o);
    void notifyObservers();
    virtual char charAt( int row, int col ) const = 0;
    virtual ~Subject() = default;
};

#endif
