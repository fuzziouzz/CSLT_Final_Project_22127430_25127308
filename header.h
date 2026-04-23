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


//Structs
struct Patient{
    int id;
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
    Medicine medicine;
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

//Functions Declaration
Patient inputPatient();
void displayPatient(const Patient& patient);
void InitMedBox();
void displayMedBox();

void clrscr();
#endif // HEADER_H