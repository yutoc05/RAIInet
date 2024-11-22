#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>
using namespace std;


void Subject::attach(unique_ptr<Observer> o) {
    observers.push_back(move(o));
}

void Subject::detach(Observer* o) {
    //pretty sure this is how to do this with unique_ptr
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (it->get() == o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyObservers() {
    //auto& may be the wrong type - please varify 
    for (auto& observer : observers) {
        observer->notify();
    }
}
