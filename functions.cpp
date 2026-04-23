//Define functions declared in header.h

#include "header.h"

void clrscr(){
    cout << "\033[2J\033[1;1H";
}

Patient inputPatient(){
    Patient patient;
    cout << "Enter patient ID: ";
    cin >> patient.id;
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, patient.name);
    cout << "Enter patient age: ";
    cin >> patient.age;
    cout << "Enter patient height (cm): ";
    cin >> patient.height;
    cout << "Enter patient weight (kg): ";
    cin >> patient.weight;
    cout << "Enter patient illness: ";
    cin.ignore();
    getline(cin, patient.illness);
    return patient;
}

void displayPatient(const Patient& patient) {
    cout << "Patient ID: " << patient.id << endl;
    cout << "Name: " << patient.name << endl;
    cout << "Age: " << patient.age << endl;
    cout << "Height: " << patient.height << " cm" << endl;
    cout << "Weight: " << patient.weight << " kg" << endl;
    cout << "Illness: " << patient.illness << endl;
}

void InitMedBox() {
    MedBox = new Medicine*[MedBoxRows];
    for (int i = 0; i < MedBoxRows; ++i) {
        MedBox[i] = new Medicine[MedBoxCols];
    }
}

void displayMed() {
    cout << "Medicine Box:" << endl;
    for (int i = 0; i < MedBoxRows; ++i) {
        for (int j = 0; j < MedBoxCols; ++j) {
            cout << "Slot [" << i << "][" << j << "]: ";
            if (MedBox[i][j].name.empty()) {
                cout << "Empty" << endl;
            } else {
                cout << MedBox[i][j].name << " (Amount: " << MedBox[i][j].amount << ")" << endl;
            }
        }
    }
}