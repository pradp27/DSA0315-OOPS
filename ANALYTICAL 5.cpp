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

    Account(int a) {
        accNo = a;
        balance = 0;
        cout << "Account Number Constructor Called" << endl;
    }

    Account(int a, double b) {
        accNo = a;
        balance = b;
        cout << "Full Details Constructor Called" << endl;
    }

    Account(const Account &A) {
        accNo = A.accNo;
        balance = A.balance;
        cout << "Copy Constructor Called" << endl;
    }

    Account operator+(double amount) {
        Account temp(*this);
        temp.balance += amount;
        return temp;
    }

    Account operator-(double amount) {
        Account temp(*this);
        temp.balance -= amount;
        return temp;
    }

    ~Account() {
        cout << "Destructor Called" << endl;
    }

    void display() {
        cout << "Account No: " << accNo
             << " Balance: " << balance << endl;
    }
};

void showAccount(Account A) {
    cout << "Inside Function" << endl;
    A.display();
}

Account createAccount() {
    Account temp(200, 10000);
    return temp;
}

int main() {
    Account A1;
    Account A2(101);
    Account A3(102, 5000);

    showAccount(A3);

    Account A4 = createAccount();

    Account A5 = A3 + 2000;
    Account A6 = A5 - 1000;

    cout << "\nFinal Account:" << endl;
    A6.display();

    return 0;
}
