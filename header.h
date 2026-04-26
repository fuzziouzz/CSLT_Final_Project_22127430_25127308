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
int MedBoxCols = 5; // Số cột của MedBox
int MedBoxRows = 5; // Số hàng của MedBox
const int MaxMedPrescription = 5; // Số lượng thuốc tối đa trong một đơn thuốc


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
    string diagnosis;
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

//Structs-Related Variables
Medicine** MedBox;
queue<Patient> patientQueue;

//Functions Declaration
Patient inputPatient();
void displayPatient(const Patient& patient);
void InitMedBox();
bool checkMedicineAvailability(string MedName, int MedAmount);
MedicalRecord TreatingPatient();
void displayMedicalRecord(const MedicalRecord& record);
void InsertToMedicalRecordList(MedicalRecordList& list, const MedicalRecord& record);


void clrscr();
#endif // HEADER_H