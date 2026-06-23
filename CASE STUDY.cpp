#include <iostream>
#include <string>
#include <vector>

using namespace std;

//==================== Doctor Class ====================

class Doctor
{
private:
    string doctorName;
    string specialization;

public:
    Doctor(string dName = "Not Assigned",
           string spec = "General")
    {
        doctorName = dName;
        specialization = spec;
    }

    void displayDoctor()
    {
        cout << "\nDoctor Name      : " << doctorName;
        cout << "\nSpecialization   : " << specialization;
    }
};

//==================== Abstract Patient Class ====================

class Patient
{
protected:
    int patientID;
    string patientName;
    int age;
    string gender;

    Doctor doctor;

public:
    Patient(int id,
            string name,
            int a,
            string g,
            string dName,
            string spec)
        : doctor(dName, spec)
    {
        this->patientID = id;
        this->patientName = name;
        this->age = a;
        this->gender = g;
    }

    // Added getter to fetch ID during discharge
    int getPatientID() const 
    {
        return patientID;
    }

    virtual double calculateBill() = 0;

    virtual void displayPatient()
    {
        cout << "\n================================";
        cout << "\nPATIENT DETAILS";
        cout << "\n================================";
        cout << "\nPatient ID    : " << patientID;
        cout << "\nPatient Name  : " << patientName;
        cout << "\nAge           : " << age;
        cout << "\nGender        : " << gender;
        doctor.displayDoctor();
    }

    virtual ~Patient() {}
};

//==================== InPatient ====================

class InPatient : virtual public Patient
{
protected:
    double roomCharge;
    double treatmentCost;
    int days;

public:
    InPatient(int id,
              string name,
              int age,
              string gender,
              string dName,
              string spec,
              double room,
              double treatment,
              int d)
        : Patient(id, name, age, gender, dName, spec)
    {
        roomCharge = room;
        treatmentCost = treatment;
        days = d;
    }

    double calculateBill()
    {
        return (roomCharge * days) + treatmentCost;
    }

    void displayPatient()
    {
        Patient::displayPatient();

        cout << "\nPatient Type  : InPatient";
        cout << "\nRoom Charge   : " << roomCharge;
        cout << "\nDays          : " << days;
        cout << "\nTreatment Cost: " << treatmentCost;
    }
};

//==================== OutPatient ====================

class OutPatient : virtual public Patient
{
private:
    double consultationFee;

public:
    OutPatient(int id,
               string name,
               int age,
               string gender,
               string dName,
               string spec,
               double fee)
        : Patient(id, name, age, gender, dName, spec)
    {
        consultationFee = fee;
    }

    double calculateBill()
    {
        return consultationFee;
    }

    void displayPatient()
    {
        Patient::displayPatient();

        cout << "\nPatient Type      : OutPatient";
        cout << "\nConsultation Fee  : " << consultationFee;
    }
};

//==================== Emergency Patient ====================

class EmergencyPatient : virtual public Patient
{
protected:
    double emergencyCharge;

public:
    EmergencyPatient(int id,
                     string name,
                     int age,
                     string gender,
                     string dName,
                     string spec,
                     double emergency)
        : Patient(id, name, age, gender, dName, spec)
    {
        emergencyCharge = emergency;
    }

    double calculateBill()
    {
        return emergencyCharge;
    }

    void displayPatient()
    {
        Patient::displayPatient();

        cout << "\nPatient Type      : Emergency";
        cout << "\nEmergency Charge  : " << emergencyCharge;
    }
};

//==================== Critical Patient ====================

class CriticalPatient : public InPatient,
                        public EmergencyPatient
{
public:
    CriticalPatient(int id,
                    string name,
                    int age,
                    string gender,
                    string dName,
                    string spec,
                    double room,
                    double treatment,
                    int d,
                    double emergency)
        : Patient(id, name, age, gender, dName, spec),
          InPatient(id, name, age, gender,
                    dName, spec,
                    room, treatment, d),
          EmergencyPatient(id, name, age, gender,
                           dName, spec,
                           emergency)
    {
    }

    double calculateBill()
    {
        return (roomCharge * days)
               + treatmentCost
               + emergencyCharge;
    }

    void displayPatient()
    {
        Patient::displayPatient();

        cout << "\nPatient Type      : Critical Patient";
        cout << "\nRoom Charge       : " << roomCharge;
        cout << "\nDays              : " << days;
        cout << "\nTreatment Cost    : " << treatmentCost;
        cout << "\nEmergency Charge  : " << emergencyCharge;
    }
};

//==================== Main ====================

int main()
{
    int choice;
    vector<Patient*> activePatients; // Vector to store multiple patients

    while (true)
    {
        Patient *patient = NULL;

        cout << "\n\n====================================";
        cout << "\n HOSPITAL MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Admit InPatient";
        cout << "\n2. Admit OutPatient";
        cout << "\n3. Admit Emergency Patient";
        cout << "\n4. Admit Critical Patient";
        cout << "\n5. Show All Patient Details"; // New Feature
        cout << "\n6. Discharge Patient";        // New Feature
        cout << "\n7. Exit";

        cout << "\n\nEnter Choice : ";
        cin >> choice;

        if (choice == 7)
        {
            cout << "\nThank You!";
            // Clean up memory before exiting
            for (Patient* p : activePatients) {
                delete p;
            }
            activePatients.clear();
            break;
        }

        // Handle Admissions (Choices 1 to 4)
        if (choice >= 1 && choice <= 4)
        {
            int id, age;
            string name, gender;
            string doctorName, specialization;

            cout << "\nEnter Patient ID : ";
            cin >> id;
            cin.ignore();

            cout << "Enter Patient Name : ";
            getline(cin, name);

            cout << "Enter Age : ";
            cin >> age;
            cin.ignore();

            cout << "Enter Gender : ";
            getline(cin, gender);

            cout << "Enter Doctor Name : ";
            getline(cin, doctorName);

            cout << "Enter Doctor Specialization : ";
            getline(cin, specialization);

            switch (choice)
            {
            case 1:
            {
                double room, treatment;
                int days;

                cout << "Room Charge Per Day : ";
                cin >> room;
                cout << "Treatment Cost : ";
                cin >> treatment;
                cout << "Days Admitted : ";
                cin >> days;

                patient = new InPatient(id, name, age, gender, doctorName, specialization, room, treatment, days);
                break;
            }
            case 2:
            {
                double fee;

                cout << "Consultation Fee : ";
                cin >> fee;

                patient = new OutPatient(id, name, age, gender, doctorName, specialization, fee);
                break;
            }
            case 3:
            {
                double emergency;

                cout << "Emergency Charge : ";
                cin >> emergency;

                patient = new EmergencyPatient(id, name, age, gender, doctorName, specialization, emergency);
                break;
            }
            case 4:
            {
                double room, treatment, emergency;
                int days;

                cout << "Room Charge Per Day : ";
                cin >> room;
                cout << "Treatment Cost : ";
                cin >> treatment;
                cout << "Days Admitted : ";
                cin >> days;
                cout << "Emergency Charge : ";
                cin >> emergency;

                patient = new CriticalPatient(id, name, age, gender, doctorName, specialization, room, treatment, days, emergency);
                break;
            }
            }

            activePatients.push_back(patient);
            cout << "\n--> Patient Admitted Successfully! <--\n";
        }
        
        // Handle Show All Patients
        else if (choice == 5) 
        {
            if (activePatients.empty()) {
                cout << "\nNo patients are currently admitted.\n";
            } else {
                for (Patient* p : activePatients) {
                    p->displayPatient();
                    cout << "\n";
                }
            }
        }
        
        // Handle Discharge Patient
        else if (choice == 6) 
        {
            if (activePatients.empty()) {
                cout << "\nNo patients to discharge.\n";
            } else {
                int searchID;
                cout << "\nEnter Patient ID to Discharge: ";
                cin >> searchID;

                bool found = false;
                for (auto it = activePatients.begin(); it != activePatients.end(); ++it) {
                    if ((*it)->getPatientID() == searchID) {
                        found = true;
                        
                        cout << "\n\n========== DISCHARGE BILL ==========";
                        (*it)->displayPatient();
                        
                        cout << "\n--------------------------------";
                        cout << "\nTOTAL BILL = Rs. " << (*it)->calculateBill();
                        cout << "\n--------------------------------\n";
                        
                        cout << "--> Patient Discharged Successfully! <--\n";

                        delete *it; // Free memory
                        activePatients.erase(it); // Remove from active list
                        break;
                    }
                }

                if (!found) {
                    cout << "\nPatient with ID " << searchID << " not found!\n";
                }
            }
        }
        else 
        {
            cout << "\nInvalid Choice!";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        if(choice == 5 || choice == 6 || choice < 1 || choice > 4) {
            cin.get(); 
        }
    }

    return 0;
}
