//
// Created by Ben on 2023-03-17.
//

#ifndef ILOGGABLE_H
#define ILOGGABLE_H

#include <iostream>
#include <string>

class ILoggable{
public:
    virtual void StringTolog() = 0;
    ~ILoggable();
    ILoggable();
};

#endif //ILOGGABLE_H

