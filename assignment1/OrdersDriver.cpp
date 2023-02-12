#include "Orders.h"

//using namespace std;

//int main() {
int orderSpace::orderMain() {

    cout << "test OrderDriver...\n" << endl;
    OrderList ordersList;

    Deploy deploy;
    Advance advance;
    Bomb bomb;
    Blockade blockade;
    Airlift airlift;
    Negotiate negotiate;

    ordersList.set_order_list(&deploy);
    ordersList.set_order_list(&advance);
    ordersList.set_order_list(&bomb);
    ordersList.set_order_list(&blockade);
    ordersList.set_order_list(&airlift);
    ordersList.set_order_list(&negotiate);

    int listSize = ordersList.get_order_list()->size();


    //print list
    cout << "Printing OrderList... \n " << endl;
    for (int i = 0; i < listSize; i++) {
        cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
    }

    //move an order
    cout << "Moving order in index 1 to index 2 \n" << endl;
    ordersList.move(1, 2);

    //print list
    cout << "Printing OrderList... \n" << endl;
    for (int i = 0; i < listSize; i++) {
        cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
    }

    //Delete an order (bomb)
    cout << "Deleting an order... \n" << endl;
    ordersList.delete_order(&bomb);

    //Print list
    cout << "Printing OrderList ... \n" << endl;
    for (int i = 0; i < listSize; i++) {
        cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
    }

    return 0;

}