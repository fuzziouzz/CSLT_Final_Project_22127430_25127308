# Smart Clinic System

## Overview

The **Smart Clinic System** is a command-line application designed to manage patient treatments, medical records, and medicine inventory for a clinic. The system provides an intuitive interface for healthcare staff to treat patients, maintain detailed medical records, and manage the medicine storage box.

## Features

### 1. **Patient Treatment Management**
- Treat patients from a pre-loaded patient queue
- Record patient information (name, age, height, weight, illness)
- Enter diagnosis for each patient
- Prescribe medicines with quantities
- Verify medicine availability in the medicine box before prescription
- Automatically save treatment records to persistent storage

### 2. **Medical Records Management**
- **View Records**: Display all stored medical records with complete patient and prescription information
- **Search Records**: Find and display medical records by patient name
- **Delete Records**: Remove specific patient records from the system
- **Persistent Storage**: All records are saved to a binary file (`MedicalRecord.bin`)
- **Empty State Notification**: Users are notified when no records are available

### 3. **Medicine Box Management**
- **Initialize Box**: Pre-loaded with 10 sample medicines (Paracetamol, Ibuprofen, Amoxicillin, etc.)
- **View Inventory**: Display all medicines and their quantities in a 4x4 grid
- **Add Medicine**: Add new medicines to empty slots in the medicine box
- **Delete Medicine**: Remove medicines from inventory
- **Availability Check**: System verifies medicine availability before allowing prescriptions

### 4. **Data Persistence**
- Medical records are saved to `MedicalRecord.bin` in binary format
- Records are automatically loaded when the program starts
- All changes are saved immediately after modifications

## How to Use

### Main Menu
When you start the program, you will see the main menu with four options:

```
------------------MAIN MENU------------------
1. Start Treating Patient
2. Medical Records
3. Medicine Box
4. Exit
---------------------------------------------
```

### Option 1: Start Treating Patient

1. Select **Option 1** from the main menu
2. A patient from the queue will be displayed with their information
3. Enter the diagnosis for the patient
4. For each medicine you want to prescribe:
   - Enter the medicine name (or type `done` to finish)
   - Enter the quantity required
   - The system will verify availability and add it to the prescription if available
5. Review the medical record and confirm (enter 'y' or 'Y')
6. The record is automatically saved and the next patient in the queue is ready for treatment
7. Press Enter to return to the main menu

### Option 2: Medical Records

1. Select **Option 2** from the main menu
2. All stored medical records will be displayed (or a notification if empty)
3. You have three sub-options:

   **Search Medical Record:**
   - Enter the patient's name to search for
   - If found, the complete medical record is displayed
   
   **Delete Medical Record:**
   - Enter the patient's name to delete
   - The record is removed and automatically saved
   
   **Return to Main Menu:**
   - Go back to the main menu

### Option 3: Medicine Box

1. Select **Option 3** from the main menu
2. The current medicine inventory is displayed (4x4 grid with slot information)
3. You have three sub-options:

   **Add Medicine:**
   - Enter the medicine name
   - Enter the quantity
   - The medicine is added to the first available empty slot
   
   **Delete Medicine:**
   - Enter the medicine name to remove
   - The medicine is deleted and the slot becomes empty
   
   **Return to Main Menu:**
   - Go back to the main menu

### Option 4: Exit

- Select **Option 4** to safely exit the program
- A thank you message is displayed

## Data Storage

### Medical Records File
- **Filename**: `MedicalRecord.bin`
- **Format**: Binary file containing serialized `MedicalRecord` structures
- **Location**: Same directory as the executable
- **Created Automatically**: If the file doesn't exist, an empty record list is created

### Record Structure
Each medical record contains:
- Patient information (name, age, height, weight, illness)
- Diagnosis
- List of prescribed medicines (up to 5) with quantities

## Compilation Instructions

### Prerequisites
- **Compiler**: GCC/G++ (or any C++11 compatible compiler)
- **Operating System**: Windows (uses MSYS2 GCC), Linux, or macOS
- **Standard Library**: C++11 or later

### Separate Compilation Steps

If you want to compile the program separately, follow these steps:

#### Step 1: Navigate to the Project Directory
```bash
cd "path/to/project/folder"
```

#### Step 2: Compile the Source Files

**Option A: Compile to Object Files (Recommended)**
```bash
g++ -c main.cpp -o main.o
g++ -c functions.cpp -o functions.o
g++ main.o functions.o -o main.exe
```

**Option B: Compile Directly to Executable**
```bash
g++ main.cpp functions.cpp -o main.exe
```

#### Step 3: Run the Program
```bash
./main.exe
```

### Compilation Flags (Optional)

For better error detection and warnings:
```bash
g++ -Wall -std=c++11 main.cpp functions.cpp -o main.exe
```

- `-Wall`: Enable all compiler warnings
- `-std=c++11`: Specify C++11 standard

### Troubleshooting Compilation Issues

| Issue | Solution |
|-------|----------|
| `command not found: g++` | Install GCC/G++ (on Windows, use MSYS2) |
| `error: 'string' does not name a type` | Ensure `#include <string>` is in header.h |
| `undefined reference to` | Check that all source files are included in compilation |
This section will be exapanded based on user report.

## Program Structure

### Files
- **main.cpp**: Main program loop and user interface
- **functions.cpp**: Implementation of all program functions
- **header.h**: Header file with struct definitions and function declarations
- **MedicalRecord.bin**: Binary database file (created automatically)

### Key Structs
- **Patient**: Stores patient demographics (name, age, height, weight, illness)
- **Medicine**: Stores medicine information (name, quantity)
- **MedicalRecord**: Combines patient info, diagnosis, and prescriptions
- **MedicalRecordNode**: Linked list node for record management
- **MedicalRecordList**: Linked list for storing all medical records

## Limitations

- Medicine box capacity: 16 medicines (4x4 grid)
- Prescription limit: 5 medicines per patient
- Patient queue: Pre-loaded with 3 sample patients
- Character array limits:
  - Patient name/illness: 100 characters
  - Diagnosis: 100 characters
  - Medicine name: 50 characters

## Future Enhancements

- Save medicine box state to persistent storage
- Patient database with admission/discharge tracking
- Medicine reordering system
- Billing and payment management
- Advanced search and filtering
- Export records to PDF/Excel formats
- Multi-user authentication

## Contact & Support

For questions or issues regarding the Smart Clinic System, please contact the development team.

---

**Version**: 1.0  
**Last Updated**: May 1, 2026
