// Everything used in "main.cpp" will be declared here

#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

// Initiating common variables
const int MedBoxCols = 4;          // Medical Box display columns
const int MedBoxRows = 4;          // Medical Box display rows
const int MaxMedPrescription = 5;  // Maximum number of medicines per prescription
const string Filename = "MedicalRecord.bin";


// Building essential structs
struct Patient {
    char name[100];
    int age;
    int height;
    int weight;
    char illness[100];
};

struct Medicine {
    int amount;
    char name[50];
};

struct MedicalRecord {
    Patient patient;
    char diagnosis[100];
    int medAmount = 0;
    Medicine prescription[MaxMedPrescription]; // Patient get maximum 5 medicines per prescription
};

// Creating linked lists
struct MedicalRecordNode {
    MedicalRecord record;
    MedicalRecordNode* next;
};
struct MedicalRecordList {
    MedicalRecordNode* head;
};


// Declaring common functions
Patient inputPatient();
void displayPatient(const Patient& patient);
void InitMedBox();
void InitPatientQueue();
bool checkMedicineAvailability(const char* MedName, int MedAmount);
MedicalRecord TreatingPatient();
void displayMedicalRecord(const MedicalRecord& record);
void AddMedicalRecord(MedicalRecordList &list, MedicalRecord newRecord);
void LoadRecordsFromFile(MedicalRecordList &list, string fileName);
void SaveRecordsToFile(MedicalRecordList list, string fileName);
void clrscr();
#endif // End of HEADER_H declaration
