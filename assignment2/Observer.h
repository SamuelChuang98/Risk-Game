//
// Created by Ben on 2023-03-17.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include "ILoggable.h"

/*
 * Abstract class that enforces subclasses to implement Update
 * Update() = 0 pure virtual method (this class will not define at all update)
 * enforces subclasses to implement virtual method
 */
class Observer {
public:
    ~Observer();
    virtual void Update(ILoggable* _log) = 0;
protected:
    Observer();
};

#endif //OBSERVER_H
