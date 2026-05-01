// Main loop
// Run this file to start the program
#include "header.h"
#include "functions.cpp"
#include <iomanip>

int main() {
    std::cout << "Welcome to the Smart Clinic System!\n";
    srand(time(0));
    MedicalRecordList MRL;
    InitMedBox();                        // Initiate the Medical Box
    InitPatientQueue();                  // Initiate the Queue for Patients
    LoadRecordsFromFile(MRL, Filename);  // Create an empty MedicalRecordList if the reuested file is not found
    std::cout << "Press the Enter key to continue...\n";
    std::cin.get();
    clrscr();
    while (true) {
        cout << "------------------MAIN MENU------------------\n";
        cout << "1. Start Treating Patient\n"; // Treating Patient
        cout << "2. Medical Records\n";        // Display Medical Records
        cout << "3. Medicine Box\n";           // Display Medicine Box
        cout << "4. Exit\n";
        cout << "---------------------------------------------\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        clrscr();
        switch (choice) {
            case 1: {
                MedicalRecord record;
                record = TreatingPatient();
                AddMedicalRecord(MRL, record);
                SaveRecordsToFile(MRL, Filename);
                cout << "Medical record saved successfully!\n";
                cout << "Press the Enter key to return to the main menu.\n";
                cin.get();
                break;
            } case 2: {
                // Display Medical Records
                // Can perform delete, search.
                // Save after edits
                bool backToMainMenu = false;
                while (!backToMainMenu) {
                    clrscr();
                    if (MRL.head == nullptr) cout << "No medical records available.\n";
                    else DisplayMedicalRecordsList(MRL);
                    cout << "\nMedical Records Menu:\n";
                    cout << "1. Search Medical Record\n";
                    cout << "2. Delete Medical Record\n";
                    cout << "3. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    int recordChoice;
                    cin >> recordChoice;
                    clrscr();
                    
                    switch (recordChoice) {
                        case 1: {
                            // Search by patient name
                            char searchName[100];
                            cout << "Enter patient name to search: ";
                            cin.ignore();
                            cin.getline(searchName, sizeof(searchName));
                            clrscr();
                            
                            MedicalRecordNode* current = MRL.head;
                            bool found = false;
                            while (current != nullptr) {
                                if (strcmp(current->record.patient.name, searchName) == 0) {
                                    found = true;
                                    displayMedicalRecord(current->record);
                                    break;
                                }
                                current = current->next;
                            }
                            
                            if (!found) cout << "Medical record for patient '" << searchName << "' does not exist.\n";
                            cout << "Press the Enter key to continue...\n";
                            cin.get();
                            clrscr();
                            break;
                        } case 2: {
                            // Delete by patient name
                            char deleteName[100];
                            cout << "Enter patient name to delete: ";
                            cin.ignore();
                            cin.getline(deleteName, sizeof(deleteName));
                            clrscr();
                            
                            if (MRL.head != nullptr && strcmp(MRL.head->record.patient.name, deleteName) == 0) {
                                MedicalRecordNode* temp = MRL.head;
                                MRL.head = MRL.head->next;
                                delete temp;
                                cout << "Medical record for patient '" << deleteName << "' has been deleted!\n";
                                SaveRecordsToFile(MRL, Filename);
                            } else {
                                MedicalRecordNode* current = MRL.head;
                                bool found = false;
                                while (current != nullptr && current->next != nullptr) {
                                    if (strcmp(current->next->record.patient.name, deleteName) == 0) {
                                        MedicalRecordNode* temp = current->next;
                                        current->next = temp->next;
                                        delete temp;
                                        found = true;
                                        cout << "Medical record for patient '" << deleteName << "' has been deleted successfully!\n";
                                        SaveRecordsToFile(MRL, Filename);
                                        break;
                                    }
                                    current = current->next;
                                }
                                if (!found) cout << "Medical record for patient '" << deleteName << "' does not exist.\n";
                            }
                            cout << "Press the Enter key to continue...\n";
                            cin.get();
                            clrscr();
                            break;
                        } case 3: {
                            backToMainMenu = true;
                            break;
                        } default: {
                            cout << "That was not a valid choice. Please try again.\n";
                            cout << "Press the Enter key to continue...\n";
                            cin.get();
                            clrscr();
                            break;
                        }
                    }
                }
                break;
            } case 3: {
                // Display Medicine Box
                // Can perform add, delete,...
                // Save after edits
                bool backToMainMenu = false;
                while (!backToMainMenu) {
                    clrscr();
                    displayMed();
                    cout << "\nMedicine Box Menu:\n";
                    cout << "1. Add Medicine\n";
                    cout << "2. Delete Medicine\n";
                    cout << "3. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    int medChoice;
                    cin >> medChoice;
                    clrscr();
                    
                    switch (medChoice) {
                        case 1: {
                            // Add medicine
                            cout << "Enter medicine name: ";
                            cin.ignore();
                            char medName[50];
                            cin.getline(medName, sizeof(medName));
                            cout << "Enter medicine amount: ";
                            int medAmount;
                            cin >> medAmount;
                            clrscr();
                            
                            bool added = false;
                            for (int i = 0; i < MedBoxRows && !added; ++i) {
                                for (int j = 0; j < MedBoxCols && !added; ++j) {
                                    if (strcmp(MedBox[i][j].name, "NaN") == 0) {
                                        strncpy(MedBox[i][j].name, medName, sizeof(MedBox[i][j].name) - 1);
                                        MedBox[i][j].name[sizeof(MedBox[i][j].name) - 1] = '\0';
                                        MedBox[i][j].amount = medAmount;
                                        cout << "Medicine '" << medName << "' has been added at slot [" << i << "][" << j << "]!\n";
                                        added = true;
                                    }
                                }
                            }
                            
                            if (!added) cout << "Medicine box is full. Cannot add more medicines.\n";
                            cout << "Press the Enter key to continue...\n";
                            cin.get();
                            clrscr();
                            break;
                        } case 2: {
                            // Delete medicine
                            cout << "Enter medicine name to delete: ";
                            cin.ignore();
                            char deleteMedName[50];
                            cin.getline(deleteMedName, sizeof(deleteMedName));
                            clrscr();
                            
                            bool deleted = false;
                            for (int i = 0; i < MedBoxRows && !deleted; ++i) {
                                for (int j = 0; j < MedBoxCols && !deleted; ++j) {
                                    if (strcmp(MedBox[i][j].name, deleteMedName) == 0) {
                                        strncpy(MedBox[i][j].name, "NaN", sizeof(MedBox[i][j].name) - 1);
                                        MedBox[i][j].name[sizeof(MedBox[i][j].name) - 1] = '\0';
                                        MedBox[i][j].amount = 0;
                                        cout << "Medicine '" << deleteMedName << "' has been deleted from slot [" << i << "][" << j << "]!\n";
                                        deleted = true;
                                    }
                                }
                            }
                            
                            if (!deleted) cout << "Medicine '" << deleteMedName << "' cannot by found in the medicine box.\n";
                            cout << "Press the Enter key to continue...\n";
                            cin.get();
                            clrscr();
                            break;
                        } case 3: {
                            backToMainMenu = true;
                            break;
                        } default: {
                            cout << "That was not a valid choice. Please try again.\n";
                            cout << "Press the Enter key to continue...\n";
                            cin.get();
                            clrscr();
                            break;
                        }
                    }
                }
                break;
            } case 4: {
                cout << "Exiting the program.\nThank you for using Smart Clinic System!\n";
                cin.get();
                return 0;
            } default: {
                cout << "That was not a valid choice. Please try again.\n";
                break;
            }
        }
    }
    return 0;
}
