//Define functions declared in header.h

#include "header.h"

void clrscr(){
    //CLEAR SCREEN
    cout << "\033[2J\033[1;1H";
}

Patient inputPatient(){
    Patient patient;
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
    cout << "Name: " << patient.name << endl;
    cout << "Age: " << patient.age << endl;
    cout << "Height: " << patient.height << " cm" << endl;
    cout << "Weight: " << patient.weight << " kg" << endl;
    cout << "Illness: " << patient.illness << endl;
}

void displayMedicalRecord(const MedicalRecord& record) {
    cout << "Patient Information:" << endl;
    displayPatient(record.patient);
    cout << "Diagnosis: " << record.diagnosis << endl;
    cout << "Prescription:" << endl;
    for (int i = 0; i < MaxMedPrescription; ++i) {
        if (!record.prescription[i].name.empty()) {
            cout << "- " << record.prescription[i].name << " (Amount: " << record.prescription[i].amount << ")" << endl;
        }
    }
}

void InitMedBox() {
    MedBox = new Medicine*[MedBoxRows];
    for (int i = 0; i < MedBoxRows; ++i) {
        MedBox[i] = new Medicine[MedBoxCols];
    }
}

bool checkMedicineAvailability(string MedName, int MedAmount) {
    for (int i = 0; i < MedBoxRows; ++i) {
        for (int j = 0; j < MedBoxCols; ++j) {
            if (MedBox[i][j].name == MedName && MedBox[i][j].amount >= MedAmount) {
                return true;
            }
        }
    }
    return false;
}

void DisplayMedicalRecords(const MedicalRecordList& list) {
    MedicalRecordNode* current = list.head;
    while (current != nullptr) {
        displayMedicalRecord(current->record);
        cout << "-------------------------------------" << endl;
        current = current->next;
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

MedicalRecord TreatingPatient(){
    cout << "Patient Remaining in Queue: " << patientQueue.size() << endl;
    cout << "-------------------------------------" << endl;
    MedicalRecord record;
    Patient patient = patientQueue.front();

    string confirmation = "N";
    while(confirmation != "Y" && confirmation != "y"){
        displayPatient(patient);
        string diagnosis;
        cout << "Enter diagnosis for the patient: ";
        cin.ignore();
        getline(cin, diagnosis);
        for (int i = 0;i<MaxMedPrescription;i++){
            string medName;
            int medAmount;
            cout << "Enter medicine name (or 'done' to finish): ";
            getline(cin, medName);
            if (medName == "done") {
                break;
            }
            cout << "Enter medicine amount: ";
            cin >> medAmount;
            cin.ignore(); 
            // Check if the medicine is available in the MedBox
            if (checkMedicineAvailability(medName, medAmount)) {

                record.prescription[i].name = medName;
                record.prescription[i].amount = medAmount;
                cout << "Medicine added to prescription." << endl;
            } else {
                cout << "Medicine not available in the MedBox." << endl;
            }
        }
        record.patient = patient;
        record.diagnosis = diagnosis;
        cout << "Please confirm the medical record (y/n): ";
        cin >> confirmation;
        clrscr();
    }
    patientQueue.pop(); 
    return record;
}

void InsertToMedicalRecordList(MedicalRecordList& list, const MedicalRecord& record) {
    MedicalRecordNode* newNode = new MedicalRecordNode;
    newNode->record = record;
    newNode->next = nullptr;

    if (list.head == nullptr) {
        list.head = newNode;
    } else {
        MedicalRecordNode* temp = list.head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

