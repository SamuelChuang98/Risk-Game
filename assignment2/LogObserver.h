//
// Created by Ben on 2023-03-17.
//

#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H
#include "Observer.h"
#include "Cards.h" //include model

class LogObserver : public Observer{
public:
    void Update(ILoggable* _log);
    void display(ILoggable* _log);

};
#endif //LOGOBSERVER_H
