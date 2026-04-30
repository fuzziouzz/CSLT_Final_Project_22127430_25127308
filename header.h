//Declare Everything Here

#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

//Variables
const int MedBoxCols = 4; // Số cột của MedBox
const int MedBoxRows = 4; // Số hàng của MedBox
const int MaxMedPrescription = 5; // Số lượng thuốc tối đa trong một đơn thuốc
const string Filename = "MedicalRecord.bin";


//Structs
struct Patient{
    string name;
    int age;
    int height;
    int weight;
    string illness;
};

struct Medicine{
    int amount;
    string name;
};

struct MedicalRecord{
    Patient patient;
    char diagnosis[100];
    int medAmount = 0;
    Medicine prescription[MaxMedPrescription]; // Patient get maximum 5 medicines per prescription
};

//Linked List
struct MedicalRecordNode{
    MedicalRecord record;
    MedicalRecordNode* next;
};
struct MedicalRecordList{
    MedicalRecordNode* head;
};


//Functions Declaration
Patient inputPatient();
void displayPatient(const Patient& patient);
void InitMedBox();
void InitPatientQueue();
bool checkMedicineAvailability(string MedName, int MedAmount);
MedicalRecord TreatingPatient();
void displayMedicalRecord(const MedicalRecord& record);
void AddMedicalRecord(MedicalRecordList &list, MedicalRecord newRecord);
void LoadRecordsFromFile(MedicalRecordList &list, string fileName);
void SaveRecordsToFile(MedicalRecordList list, string fileName);
void clrscr();
#endif // HEADER_H