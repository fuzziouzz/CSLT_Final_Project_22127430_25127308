// Define functions declared in header.h
#include "header.h"

// Structs-Related Variables
Medicine** MedBox;
queue<Patient> patientQueue;

void clrscr() {
    // Shortened of Clear Screen
    system("cls||clear");
}



Patient ConstructPatientInfo(const char* name, int age, int height, int weight, const char* illness) {
    Patient patient;
    strncpy(patient.name, name, sizeof(patient.name) - 1);
    patient.name[sizeof(patient.name) - 1] = '\0';
    patient.age = age;
    patient.height = height;
    patient.weight = weight;
    strncpy(patient.illness, illness, sizeof(patient.illness) - 1);
    patient.illness[sizeof(patient.illness) - 1] = '\0';
    return patient;
}

void InitPatientQueue() {
    // Initialize the patient queue with some sample patients
    patientQueue.push(ConstructPatientInfo("John Doe", 30, 175, 70, "Vomiting, Diarrhea"));
    patientQueue.push(ConstructPatientInfo("Jane Smith", 25, 160, 55, "Sore Throat, Runny Nose"));
    patientQueue.push(ConstructPatientInfo("Alice Johnson", 40, 165, 60, "Headache, Fever"));
}

Patient inputPatient() {
    Patient patient;
    cout << "Enter patient name: ";
    cin.ignore();
    cin.getline(patient.name, sizeof(patient.name));
    cout << "Enter patient age: ";
    cin >> patient.age;
    cout << "Enter patient height (cm): ";
    cin >> patient.height;
    cout << "Enter patient weight (kg): ";
    cin >> patient.weight;
    cout << "Enter patient illness: ";
    cin.ignore();
    cin.getline(patient.illness, sizeof(patient.illness));
    return patient;
}

void displayPatient(const Patient& patient) {
    cout << "Name: " << patient.name << endl;
    cout << "Age: " << patient.age << endl;
    cout << "Height: " << patient.height << " cm\n";
    cout << "Weight: " << patient.weight << " kg\n";
    cout << "Illness: " << patient.illness << endl;
}

void displayMedicalRecord(const MedicalRecord& record) {
    cout << "Patient Information:\n";
    displayPatient(record.patient);
    cout << "Diagnosis: " << record.diagnosis << endl;
    cout << "Number of Medicines Prescribed: " << record.medAmount << endl;
    cout << "Prescription:" << endl;
    for (int i = 0; i < MaxMedPrescription; ++i) {
        if (strcmp(record.prescription[i].name, "") != 0) {
            cout << " - " << record.prescription[i].name << " (Amount: " << record.prescription[i].amount << ")\n";
        }
    }
}

void InitMedBox() {
    MedBox = new Medicine*[MedBoxRows];
    for (int i = 0; i < MedBoxRows; ++i) {
        MedBox[i] = new Medicine[MedBoxCols];
    }

    const char* sampleNames[] = {
        "Paracetamol", "Ibuprofen", "Amoxicillin", "Loratadine", "Omeprazole",
        "Aspirin", "Cetirizine", "Diclofenac", "Augmentin", "Decolgen"
    };

    // 3. Initiate some values
    int drugCount = 0;
    for (int i = 0; i < MedBoxRows; ++i) {
        for (int j = 0; j < MedBoxCols; ++j) {
            // Fill info for the first 10 cells, the rest will be left empty
            if (drugCount < 10) {
                strncpy(MedBox[i][j].name, sampleNames[drugCount], sizeof(MedBox[i][j].name) - 1);
                MedBox[i][j].name[sizeof(MedBox[i][j].name) - 1] = '\0';
                MedBox[i][j].amount = rand() % 6 + 5; // Pick a random integer within the [5, 10] range
                drugCount++;
            } else {
                strncpy(MedBox[i][j].name, "NaN", sizeof(MedBox[i][j].name) - 1);
                MedBox[i][j].name[sizeof(MedBox[i][j].name) - 1] = '\0';
                MedBox[i][j].amount = 0;
            }
        }
    }
    cout << "Medicine Box initialized successfully!\n";
}

bool checkMedicineAvailability(const char* MedName, int MedAmount) {
    for (int i = 0; i < MedBoxRows; ++i) {
        for (int j = 0; j < MedBoxCols; ++j) {
            if (strcmp(MedBox[i][j].name, MedName) == 0 && MedBox[i][j].amount >= MedAmount) return true;
        }
    }
    return false;
}

void DisplayMedicalRecordsList(const MedicalRecordList& list) {
    MedicalRecordNode* current = list.head;
    while (current != nullptr) {
        displayMedicalRecord(current->record);
        cout << "-------------------------------------\n";
        current = current->next;
    }
}

void displayMed() {
    cout << "Medicine Box:" << endl;
    for (int i = 0; i < MedBoxRows; ++i) {
        for (int j = 0; j < MedBoxCols; ++j) {
            cout << "Slot [" << i << "][" << j << "]: ";
            if (strcmp(MedBox[i][j].name, "NaN") == 0) cout << "Empty\n";
            else cout << MedBox[i][j].name << " (Amount: " << MedBox[i][j].amount << ")\n";
        }
    }
}

MedicalRecord TreatingPatient() {
    cout << "Patient Remaining in Queue: " << patientQueue.size() << endl;
    cout << "-------------------------------------\n";
    MedicalRecord record;
    memset(&record, 0, sizeof(record));
    Patient patient = patientQueue.front();

    string confirmation = "N";
    while (confirmation != "Y" && confirmation != "y") {
        displayPatient(patient);
        char diagnosis[100];
        cout << "Enter diagnosis for the patient: ";
        cin.ignore();
        cin.getline(diagnosis, sizeof(diagnosis));
        for (int i = 0; i < MaxMedPrescription; i++) {
            char medName[50];
            int medAmount;
            cout << "Enter medicine name (or 'done' to finish): ";
            cin.getline(medName, sizeof(medName));
            if (strcmp(medName, "done") == 0) break;
            cout << "Enter medicine amount: ";
            cin >> medAmount;
            cin.ignore(); 
            // Check if the medicine is available in the Medical Box
            if (checkMedicineAvailability(medName, medAmount)) {
                strncpy(record.prescription[i].name, medName, sizeof(record.prescription[i].name) - 1);
                record.prescription[i].name[sizeof(record.prescription[i].name) - 1] = '\0';
                record.prescription[i].amount = medAmount;
                cout << "Medicine added to prescription.\n";
                record.medAmount++;
            } else cout << "Medicine not available in the MedBox.\n";
        }
        record.patient = patient;
        strncpy(record.diagnosis, diagnosis, sizeof(record.diagnosis) - 1);
        record.diagnosis[sizeof(record.diagnosis) - 1] = '\0';
        cout << "Please confirm the medical record (y/n): ";
        cin >> confirmation;
        clrscr();
    }
    patientQueue.pop(); 
    return record;
}

void AddMedicalRecord(MedicalRecordList &list, MedicalRecord newRecord) {
    MedicalRecordNode* newNode = new MedicalRecordNode;
    newNode->record = newRecord; // Copy Meidcal Record data
    newNode->next = list.head;   // Point new node to current head
    list.head = newNode;         // Update the new head
}

void SaveRecordsToFile(MedicalRecordList list, string fileName) {
    ofstream outFile(fileName, ios::binary | ios::trunc);
    MedicalRecordNode* curr = list.head;
    while (curr != nullptr) {
        outFile.write(reinterpret_cast<const char*>(&(curr->record)), sizeof(MedicalRecord));
        curr = curr->next;
    }
    outFile.close();
}

void LoadRecordsFromFile(MedicalRecordList &list, string fileName) {
    ifstream inFile(fileName, ios::binary | ios::ate);
    
    if (!inFile) {
        cout << "File not found. Starting with an empty medical record list.\n";
        list.head = nullptr;
        return;
    }

    list.head = nullptr;
    MedicalRecordNode* tail = nullptr;

    streamsize size = inFile.tellg(); 
    if (size == 0) {
        cout << "Found an empty medical records file.\n";
        list.head = nullptr;
        inFile.close();
        return;
    }

    inFile.seekg(0, ios::beg);

    MedicalRecord tempRecord;
    cout << "Loading medical records from file...\n";
    while (inFile.read(reinterpret_cast<char*>(&tempRecord), sizeof(MedicalRecord))) {
        cout << "...";
        MedicalRecordNode* newNode = new MedicalRecordNode;
        newNode->record = tempRecord;
        newNode->next = nullptr;

        if (list.head == nullptr) {
            list.head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "Medical records loaded successfully!\n";
    inFile.close();
}
