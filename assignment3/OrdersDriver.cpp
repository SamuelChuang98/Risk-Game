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
    listSize = ordersList.get_order_list()->size();

    cout << "Printing OrderList ... \n" << endl;
    for (int i = 0; i < listSize; i++) {
        cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
    }


    // =============== Project 2 demonstrations begins here ===================

    // Must demonstrate the following:

    // (1) each order is validated before being executed according to the above descriptions;
    // (2) ownership of a territory is transferred to the attacking player if a territory is conquered as a result of an advance order;
    // (3) one card is given to a player if they conquer at least one territory in a turn (not more than one card per turn);
    // (4) the negotiate order prevents attacks between the two players involved;
    // (5) the blockade order transfers ownership to the Neutral player;
    // 6) all the orders described above can be issued by a player and executed by the game engine.

    ordersList.execute_orders();

    return 0;

}