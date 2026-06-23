#include <iostream>
using namespace std;

class Product {
    int stock;

public:
    Product(int s) {
        stock = s;
        cout << "Parameterized Constructor Called" << endl;
    }

    Product(const Product &p) {
        stock = p.stock;
        cout << "Copy Constructor Called" << endl;
    }

    Product operator+(const Product &p) {
        Product temp(stock + p.stock);
        return temp;
    }

    ~Product() {
        cout << "Destructor Called" << endl;
    }

    void display() {
        cout << "Stock = " << stock << endl;
    }
};

int main() {
    Product p1(50);
    Product p2(30);

    Product p3 = p1;
    Product p4 = p1 + p2;

    cout << "\nInventory Details:" << endl;
    p3.display();
    p4.display();

    return 0;
}
