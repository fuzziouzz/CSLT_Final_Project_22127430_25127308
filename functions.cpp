//Define functions declared in header.h
#include "header.h"

//Structs-Related Variables
Medicine** MedBox;
queue<Patient> patientQueue;

void clrscr(){
    //CLEAR SCREEN
    cout << "\033[2J\033[1;1H";
}



Patient ConstructorPatient(string name, int age, int height, int weight, string illness){
    Patient patient;
    patient.name = name;
    patient.age = age;
    patient.height = height;
    patient.weight = weight;
    patient.illness = illness;
    return patient;
}

void InitPatientQueue() {
    // Initialize the patient queue with some sample patients
    patientQueue.push(ConstructorPatient("John Doe", 30, 175, 70, "Vomiting, Diarrhea"));
    patientQueue.push(ConstructorPatient("Jane Smith", 25, 160, 55, "Sore Throat, Runny Nose"));
    patientQueue.push(ConstructorPatient("Alice Johnson", 40, 165, 60, "Headache, Fever"));
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
    cout << "Number of Medicines Prescribed: " << record.medAmount << endl;
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

    string sampleNames[] = {
        "Paracetamol", "Ibuprofen", "Amoxicillin", "Loratadine", "Omeprazole",
        "Aspirin", "Cetirizine", "Diclofenac", "Augmentin", "Decolgen"
    };

    // 3. Khởi tạo giá trị ban đầu
    int drugCount = 0;
    for (int i = 0; i < MedBoxRows; ++i) {
        for (int j = 0; j < MedBoxCols; ++j) {
            // Chỉ đổ dữ liệu cho 10 ô đầu tiên, còn lại để trống
            if (drugCount < 10) {
                MedBox[i][j].name = sampleNames[drugCount];
                MedBox[i][j].amount = rand() % 6 + 5; // Ngẫu nhiên 5-10
                drugCount++;
            } else {
                MedBox[i][j].name = "NaN";
                MedBox[i][j].amount = 0;
            }
        }
    }
    cout << "Medicine Box initialized successfully!" << endl;
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

void DisplayMedicalRecordsList(const MedicalRecordList& list) {
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
            if (MedBox[i][j].name == "NaN") {
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
        char diagnosis[100];
        cout << "Enter diagnosis for the patient: ";
        cin.ignore();
        cin.getline(diagnosis, sizeof(diagnosis));
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
                record.medAmount++;
            } else {
                cout << "Medicine not available in the MedBox." << endl;
            }
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
    newNode->record = newRecord; // Sao chép dữ liệu bệnh án
    newNode->next = list.head;   // Trỏ node mới vào head hiện tại
    list.head = newNode;         // Cập nhật head mới
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
        cout << "File not found. Starting with an empty medical record list." << endl;
        list.head = nullptr;
        return;
    }

    list.head = nullptr;
    MedicalRecordNode* tail = nullptr;

    streamsize size = inFile.tellg(); 
    if (size == 0) {
        cout << "Found an empty medical records file." << endl;
        list.head = nullptr;
        inFile.close();
        return;
    }

    inFile.seekg(0, ios::beg);

    MedicalRecord tempRecord;
    cout << "Loading medical records from file..." << endl;
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
    cout << "Medical records loaded successfully!" << endl;
    inFile.close();
}