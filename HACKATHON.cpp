#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class User {
protected:
    string name;
    string role;

public:
    User(string n, string r) {
        name = n;
        role = r;
    }

    virtual void displayRole() {
        cout << "\nName : " << name;
        cout << "\nRole : " << role << endl;
    }

    string getName() {
        return name;
    }
};

class Citizen : public User {
public:
    Citizen(string n) : User(n, "Citizen") {}

    void displayRole() override {
        cout << "\nCitizen: " << name << endl;
    }
};

class Official : public User {
public:
    Official(string n) : User(n, "Official") {}

    void displayRole() override {
        cout << "\nOfficial: " << name << endl;
    }
};

class HazardReport {
private:
    string reporter;
    string hazardType;
    string location;
    string description;

public:
    HazardReport(string r, string h, string l, string d) {
        reporter = r;
        hazardType = h;
        location = l;
        description = d;
    }

    void displayReport() {
        cout << "\n--------------------------------";
        cout << "\nReporter    : " << reporter;
        cout << "\nHazard Type : " << hazardType;
        cout << "\nLocation    : " << location;
        cout << "\nDescription : " << description;
        cout << "\n--------------------------------\n";
    }

    void saveToFile() {
        ofstream file("reports.txt", ios::app);

        file << reporter << "|"
             << hazardType << "|"
             << location << "|"
             << description << endl;

        file.close();
    }
};

class OceanHazardSystem {
private:
    vector<HazardReport> reports;

public:
    void submitReport(string userName) {
        string type, location, desc;

        cin.ignore();

        cout << "\nEnter Hazard Type: ";
        getline(cin, type);

        cout << "Enter Location: ";
        getline(cin, location);

        cout << "Enter Description: ";
        getline(cin, desc);

        try {
            if (type.empty() || location.empty())
                throw "Hazard Type and Location cannot be empty!";
        }
        catch (const char* msg) {
            cout << "\nError: " << msg << endl;
            return;
        }

        HazardReport r(userName, type, location, desc);

        reports.push_back(r);
        r.saveToFile();

        cout << "\nReport Submitted Successfully!\n";
    }

    void viewReports() {
        if (reports.empty()) {
            cout << "\nNo Reports Available.\n";
            return;
        }

        for (auto &r : reports)
            r.displayReport();
    }
};

int main() {

    OceanHazardSystem system;

    int choice;

    do {
        cout << "\n===== OCEAN HAZARD REPORTING SYSTEM =====";
        cout << "\n1. Citizen Login";
        cout << "\n2. Official Login";
        cout << "\n3. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            string name;
            cout << "\nEnter Citizen Name: ";
            cin >> name;

            Citizen c(name);
            c.displayRole();

            int ch;
            do {
                cout << "\n1. Submit Hazard Report";
                cout << "\n2. View Reports";
                cout << "\n3. Logout";
                cout << "\nEnter Choice: ";
                cin >> ch;

                switch (ch) {
                case 1:
                    system.submitReport(c.getName());
                    break;

                case 2:
                    system.viewReports();
                    break;

                case 3:
                    cout << "\nLogged Out.\n";
                    break;

                default:
                    cout << "\nInvalid Choice!\n";
                }

            } while (ch != 3);

            break;
        }

        case 2: {
            string name;
            cout << "\nEnter Official Name: ";
            cin >> name;

            Official o(name);
            o.displayRole();

            system.viewReports();
            break;
        }

        case 3:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}
