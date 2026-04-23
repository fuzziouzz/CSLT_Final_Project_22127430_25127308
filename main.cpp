//Main loop
//Run this file to start the program

#include "header.h"
#include <iomanip>


int main() {
    cout << "Welcome to the Smart Clinic System!" << endl;
    cout << "Press any key to continue..." << endl;
    cin.get();
    clrscr();
    while(1){
        cout << "1. Start " << endl;
        cout << "2. Medical records" << endl;
        cout << "3. Medicine Box" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        clrscr();
        switch (choice) {
            case 1: {
                
                break;
            }
            case 2: {
                
                break;
            }
            case 3: {
                
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
