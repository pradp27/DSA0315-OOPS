#include <iostream>
using namespace std;

class Account {
    int accNo;
    double balance;

public:
    Account() {
        accNo = 0;
        balance = 0;
        cout << "Default Constructor Called" << endl;
    }
    Account(int a, double b) {
        accNo = a;
        balance = b;
        cout << "Parameterized Constructor Called" << endl;
    }
    Account(const Account &obj) {
        accNo = obj.accNo;
        balance = obj.balance;
        cout << "Copy Constructor Called" << endl;
    }

    void display() {
        cout << "Account No: " << accNo
             << ", Balance: " << balance << endl;
    }
};

int main() {
    Account A1;
    Account A2(101, 5000);
    Account A3 = A2;
    cout << "\nAccount Details:" << endl;
    A1.display();
    A2.display();
    A3.display();

    return 0;
}
