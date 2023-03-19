//
// Created by Ben on 2023-03-17.
//

#include "LogObserver.h"
#include "ILoggable.h"
#include <iostream>

void LogObserver:: Update(ILoggable* _log){
    display(_log);
};

void LogObserver:: display(ILoggable* _log){
    _log->StringTolog();
};