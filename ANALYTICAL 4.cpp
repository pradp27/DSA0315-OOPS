#include <iostream>
#include <cstring>
using namespace std;
class Product {
    int id, quantity;
    char *name;

public:
    Product(int i, const char *n, int q) {
        id = i;
        quantity = q;

        name = new char[strlen(n) + 1];
        strcpy(name, n);

        cout << "Parameterized Constructor Called" << endl;
    }

    Product(const Product &p) {
        id = p.id;
        quantity = p.quantity;

        name = new char[strlen(p.name) + 1];
        strcpy(name, p.name);

        cout << "Copy Constructor Called" << endl;
    }

    Product operator+(const Product &p) {
        Product temp(id, name, quantity + p.quantity);
        return temp;
    }

    ~Product() {
        delete[] name;
        cout << "Destructor Called" << endl;
    }

    void display() {
        cout << "ID: " << id
             << ", Name: " << name
             << ", Quantity: " << quantity << endl;
    }
};

int main() {
    Product p1(101, "Laptop", 10);
    Product p2 = p1;
    Product p3(102, "Laptop", 5);

    Product total = p1 + p3;
    cout << "\nProduct Details:" << endl;
    p2.display();
    total.display();

    return 0;
}
