//Main loop
//Run this file to start the program

#include "header.h"
#include <iomanip>

Patient ConstructorPatient(string name, int age, int height, int weight, string illness){
    Patient patient;
    patient.name = name;
    patient.age = age;
    patient.height = height;
    patient.weight = weight;
    patient.illness = illness;
    return patient;
}

int main() {
    cout << "Welcome to the Smart Clinic System!" << endl;
    cout << "Press any key to continue..." << endl;
    cin.get();
    clrscr();
    while(1){
        cout << "------------------MAIN MENU------------------" << endl;
        cout << "1. Start Treating Patient" << endl; //Treating Patient
        cout << "2. Medical records" << endl;        //Display Medical Records
        cout << "3. Medicine Box" << endl;           //Display Medicine Box
        cout << "4. Exit" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        clrscr();
        switch (choice) {
            case 1: {
                MedicalRecord record;
                record = TreatingPatient();

                break;
            }
            case 2: {
                
                break;
            }
            case 3: {
                
                break;
            }
            case 4: {
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
        
    }
    return 0;
}
