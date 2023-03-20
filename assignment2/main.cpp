//
// Created by Ben on 2023-02-08.
//
//#include "Cards.h"
//#include "Player.h"
// #include "Orders.h"
// #include "Map.h"
#include "GameEngine.h"
#include "LogObserver.h"

int main() {
    //cardSpace::cardsMain();
    //playerSpace::playerMain();
    // orderSpace::orderMain();
    // mapSpace::mapMain();
    GameEngineSpace::GameEngineMain();

    Order *order = new Order();
    LogObserver *observer = new LogObserver();

    order->Attach(observer);
    delete observer;
    delete order;
}