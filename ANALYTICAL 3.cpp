#include <iostream>
using namespace std;

class ShoppingCart {
    int items;

public:
    ShoppingCart(int i) {
        items = i;
        cout << "Parameterized Constructor Called" << endl;
    }

    ShoppingCart(const ShoppingCart &c) {
        items = c.items;
        cout << "Copy Constructor Called" << endl;
    }

    ShoppingCart operator+(const ShoppingCart &c) {
        ShoppingCart temp(items + c.items);
        return temp;
    }

    ~ShoppingCart() {
        cout << "Destructor Called" << endl;
    }

    void display() {
        cout << "Items in Cart = " << items << endl;
    }
};

int main() {
    ShoppingCart cart1(5);
    ShoppingCart cart2(3);

    ShoppingCart cart3 = cart1;
    ShoppingCart merged = cart1 + cart2;

    cout << "\nCart Details:" << endl;
    cart3.display();
    merged.display();

    return 0;
}
