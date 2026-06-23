#include <iostream>
#include <string>
using namespace std;

class BankAccount {
protected:
    int accNo;
    string name;
    double balance;

public:
    BankAccount() {
        accNo = 0;
        name = "";
        balance = 0;
    }

    BankAccount(int a, string n, double b) {
        accNo = a;
        name = n;
        balance = b;
    }

    int getAccNo() {
        return accNo;
    }

    string getName() {
        return name;
    }

    void deposit(double amount) {
        if (amount <= 0)
            throw "Invalid Deposit Amount";

        balance += amount;
        cout << "Deposit Successful\n";
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw "Invalid Withdrawal Amount";

        if (amount > balance)
            throw "Insufficient Balance";

        balance -= amount;
        cout << "Withdrawal Successful\n";
    }

    void checkMinBalance() {
        if (balance < 1000)
            throw "Minimum Balance Violated";
    }

    virtual void display() {
        cout << "\nAccount Number : " << accNo;
        cout << "\nAccount Holder : " << name;
        cout << "\nBalance        : Rs." << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
    double interestRate;

public:
    SavingsAccount() : BankAccount() {
        interestRate = 0;
    }

    SavingsAccount(int a, string n, double b, double r)
        : BankAccount(a, n, b) {
        interestRate = r;
    }

    void addInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest Added: Rs." << interest << endl;
    }

    void display() override {
        BankAccount::display();
        cout << "Interest Rate  : " << interestRate << "%" << endl;
    }
};

class Transaction {
public:
    void transfer(double amount) {
        cout << "Transferred Rs." << amount << endl;
    }

    void transfer(double amount, string receiver) {
        cout << "Transferred Rs." << amount
             << " to " << receiver << endl;
    }
};

class FixedDeposit {
    double amount;
    double rate;
    int years;

public:
    FixedDeposit(double a, double r, int y) {
        amount = a;
        rate = r;
        years = y;
    }

    void calculateMaturity() {
        double maturity = amount;

        for (int i = 0; i < years; i++)
            maturity += maturity * rate / 100;

        cout << "FD Maturity Amount: Rs." << maturity << endl;
    }
};

class Loan {
    double loanAmount;
    double interestRate;
    int years;

public:
    Loan(double l, double r, int y) {
        loanAmount = l;
        interestRate = r;
        years = y;
    }

    void calculateLoanAmount() {
        double total =
            loanAmount + (loanAmount * interestRate * years) / 100;

        cout << "Total Loan Repayment Amount: Rs." << total << endl;
    }
};

int main() {
    int n;

    cout << "===== BANK MANAGEMENT SYSTEM =====\n";

    cout << "Enter Number of Accounts: ";
    cin >> n;

    SavingsAccount accounts[50];

    for (int i = 0; i < n; i++) {
        int accNo;
        string name;
        double balance, rate;

        cout << "\nEnter Details for Account " << i + 1 << endl;

        cout << "Account Number: ";
        cin >> accNo;

        cout << "Account Holder Name: ";
        cin >> name;

        cout << "Initial Balance: ";
        cin >> balance;

        cout << "Interest Rate (%): ";
        cin >> rate;

        accounts[i] = SavingsAccount(accNo, name, balance, rate);
    }

    try {
        int searchAccNo;
        bool found = false;

        cout << "\nEnter Account Number to Manage: ";
        cin >> searchAccNo;

        for (int i = 0; i < n; i++) {
            if (accounts[i].getAccNo() == searchAccNo) {

                found = true;

                cout << "\n===== ACCOUNT FOUND =====\n";
                accounts[i].display();

                double depAmt;
                cout << "\nEnter Deposit Amount: ";
                cin >> depAmt;
                accounts[i].deposit(depAmt);

                double wdAmt;
                cout << "Enter Withdrawal Amount: ";
                cin >> wdAmt;
                accounts[i].withdraw(wdAmt);

                accounts[i].checkMinBalance();

                accounts[i].addInterest();

                cout << "\n===== UPDATED ACCOUNT DETAILS =====\n";
                accounts[i].display();

                Transaction t;

                double transferAmt;
                string receiver;

                cout << "\nEnter Transfer Amount: ";
                cin >> transferAmt;

                t.transfer(transferAmt);

                cout << "Enter Receiver Name: ";
                cin >> receiver;

                t.transfer(transferAmt, receiver);

                int fdChoice;
                cout << "\nCreate Fixed Deposit? (1-Yes / 0-No): ";
                cin >> fdChoice;

                if (fdChoice == 1) {
                    double fdAmount, fdRate;
                    int fdYears;

                    cout << "FD Amount: ";
                    cin >> fdAmount;

                    cout << "FD Interest Rate: ";
                    cin >> fdRate;

                    cout << "FD Duration (Years): ";
                    cin >> fdYears;

                    FixedDeposit fd(fdAmount, fdRate, fdYears);
                    fd.calculateMaturity();
                }

                int loanChoice;
                cout << "\nApply for Loan? (1-Yes / 0-No): ";
                cin >> loanChoice;

                if (loanChoice == 1) {
                    double loanAmt, loanRate;
                    int loanYears;

                    cout << "Loan Amount: ";
                    cin >> loanAmt;

                    cout << "Loan Interest Rate: ";
                    cin >> loanRate;

                    cout << "Loan Duration (Years): ";
                    cin >> loanYears;

                    Loan loan(loanAmt, loanRate, loanYears);
                    loan.calculateLoanAmount();
                }

                break;
            }
        }

        if (!found)
            throw "Account Not Found";
    }

    catch (const char* error) {
        cout << "\nError: " << error << endl;
    }

    cout << "\n===== THANK YOU =====\n";

    return 0;
}
