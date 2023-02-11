#include "Orders.h"


int orderSpace::orderMain() {
    cout << "test OrderDriver...\n" << endl;
    OrderList ordersList;

    Deploy aDeploy;
    Advance anadvance;
    Bomb abomb;
    Blockade ablockade;
    Airlift anairlift;
    Negotiate anegotiate;

    ordersList.set_order_list(&aDeploy);
    ordersList.set_order_list(&anadvance);
    ordersList.set_order_list(&abomb);
    ordersList.set_order_list(&ablockade);
    ordersList.set_order_list(&anairlift);
    ordersList.set_order_list(&anegotiate);


    //print orderlist
    cout << "\n the orderlist contains: " << endl;
    for (int i = 0; i < ordersList.get_order_list()->size(); i++) {
        cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
    }

    //delete an order
    ordersList.delete_order(&aDeploy);

    //print orderlist
    cout << "\n the orderlist contains: " << endl;
    for (int i = 0; i < ordersList.get_order_list()->size(); i++) {
        cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
    }

    //move an order
    ordersList.move(0, 4);
    //ordersList.move(0, 5);
    ordersList.move(0, 8);//invalid
    //print orderlist
    cout << "\n the orderlist contains: " << endl;
    for (int i = 0; i < ordersList.get_order_list()->size(); i++) {
        cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
    }

    return 0;

}