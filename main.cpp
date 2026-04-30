//Main loop
//Run this file to start the program
#include "header.h"
#include <iomanip>

int main() {
    cout << "Welcome to the Smart Clinic System!" << endl;
    srand(time(0));
    MedicalRecordList MedicalRecordList;
    InitMedBox();
    InitPatientQueue();
    LoadRecordsFromFile(MedicalRecordList, Filename); //Create an empty MedicalRecordList if File not found
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
                AddMedicalRecord(MedicalRecordList, record);
                SaveRecordsToFile(MedicalRecordList, Filename);
                cout << "Medical record saved successfully!" << endl;
                cout << "Press any key to return to the main menu..." << endl;
                cin.get();
                break;
            }
            case 2: {
                // Display Medical Reecords
                // Can perform delete, search.
                // Save after edits
                break;
            }
            case 3: {
                // Display Medicine Box
                // Can perform add, delete,...
                // Save after edits
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
