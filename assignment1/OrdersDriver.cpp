 #include "Orders.h"

using namespace std;

	/*Deploy::Deploy() {
  	// constructor implementation here
	}

	Deploy::~Deploy() {
	// destructor implementation here
	}

	Advance::Advance() {
	// implementation of Advance constructor
	}

	Advance::~Advance() {
	// implementation of Advance constructor
	}

	Bomb::Bomb() {
	// implementation of Bomb constructor
	}

	Bomb::~Bomb() {
	// implementation of Bomb constructor
	}

	Blockade::Blockade() {
	// implementation of Blockade constructor
	}

	Blockade::~Blockade() {
	// implementation of Blockade constructor
	}

	Airlift::Airlift() {
	// implementation of Airlift constructor
	}

	Airlift::~Airlift() {
	// implementation of Airlift constructor
	}

	Negotiate::Negotiate() {
	// implementation of Negotiate constructor
	}

	Negotiate::~Negotiate() {
	// implementation of Negotiate constructor
	}

	Order::Order() {
	// implementation of Negotiate constructor
	}

	Order::~Order() {
	// implementation of Negotiate constructor
	}*/

int main()
{
	cout << "test OrderDriver...\n" << endl;

	cout << "----------------------------" << endl;

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

	//print orderlist
	cout << "\n the orderlist contains: " << endl;
	for (int i = 0; i < ordersList.get_order_list()->size(); i++) {
		cout <<"  "<< ordersList.get_order_list()->at(i)->get_type() << endl;
	}

	//delete an order
	ordersList.delete_order(&deploy);

	//print orderlist
	cout << "\n the orderlist contains: " << endl;
	for (int i = 0; i < ordersList.get_order_list()->size(); i++) {
		cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
	}

	//move an order
	ordersList.move(0,4);
	//ordersList.move(0, 5);
	ordersList.move(0, 8);//invalid
	//print orderlist
	cout << "\n the orderlist contains: " << endl;
	for (int i = 0; i < ordersList.get_order_list()->size(); i++) {
		cout << "  " << ordersList.get_order_list()->at(i)->get_type() << endl;
	}

}