//
// Created by Ben on 2023-03-17.
//

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include "ILoggable.h"
#include <list>
using namespace std;

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(ILoggable* _log);
    Subject();
    ~Subject();
private:
    list<Observer*>* _observers;
};

#endif //SUBJECT_H
