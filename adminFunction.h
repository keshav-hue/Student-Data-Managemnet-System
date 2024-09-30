#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>       
#include <string>       
#include <fstream>
#include <sstream>      // For std::stringstream
#include <thread>
#include <iomanip>
#include <cstdlib>
#include <chrono>
using namespace std;

void addData(void);
void viewData(void);
void mainMenu(void);
void updateData(void);
void deleteData(void);
void adminVerification(void);
void studentFunction(void);

void adminFunction()
{
    system("clear");
    cout << "\n\n\t\t\t\t\t | Logged In as Admin |\n";
    cout << "\n\n\t\t\t\t\t 1. Add Students Detail";
    cout << "\n\n\t\t\t\t\t 2. Delete Students";
    cout << "\n\n\t\t\t\t\t 3. Update Record";
    cout << "\n\n\t\t\t\t\t 4. View Table ";
    cout << "\n\n\t\t\t\t\t 5. Main Menu ";
    cout << "\n\n\t\t\t\t\t 6. Exit";

    int option;
    cout << "\n\n\t\t\t\t\tEnter choice : ";
    do
    {
        cin >> option;

        {
            switch (option)
            {

            case 1:
                addData();
                break;

            case 2:
                deleteData();
                break;

            case 3:
                cout<<"It is under progress"<<endl;//updateData();
                exit(0);
		break;

            case 4:
                viewData();
                break;

            case 5:
                mainMenu();
                break;

            case 6:
                system("clear");
                cout << "\t\t\n\n\n\n\n\n\n\t\t\t\t\tQuitting The Program...";
		cout << "\t\t\n\n\n\n";
                for (int i = 0; i < 1; i++)
                {

                    sleep(1);
        
                }
                exit(0);
                break;

            default:
                system("clear");
                cout << "\n\n\t\t\t\t\t Logged In as Admin";
                cout << "\n\n\t\t\t\t\t 1. Add Students Record";
                cout << "\n\n\t\t\t\t\t 2. Delete Record";
                cout << "\n\n\t\t\t\t\t 3. Update Record";
                cout << "\n\n\t\t\t\t\t 4. View Table ";
                cout << "\n\n\t\t\t\t\t 5. Main Menu ";
                cout << "\n\n\t\t\t\t\t 6. Exit";

                cout << "\n\n\t\t\t\t\t invalid input!";

                cout << "\n\n\t\t\t\t\t Enter choice : ";
            }
        }

    } while (option != '6');
}

void mainMenu()
{
    system("clear");

    cout << "\n\n\n\n\t\t\t\t\t Login As : ";
    cout << "\n\n\n\t\t\t\t\t 1. Admin ";
    cout << "\n\n\t\t\t\t\t 2. Student";
    cout << "\n\n\t\t\t\t\t 3. Exit";
    cout << "\n\n\n\t\t\t\t\t Enter your choice : ";

    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        adminVerification();
        break;

    case 2:
        system("clear");

        cout << "Welcome as Student";
	
        studentFunction();
        break;

    case 3:
        system("clear");
        cout << "\t\t\n\n\n\n\n\n\n\t\t\t\t\tQuitting The Program...";
	cout << "\t\t\n\n\n" <<endl;
        for (int i = 0; i < 1; i++)
        {

            sleep(1);
            
        }

        exit(0);
        break;

    default:
        cout << "invalid input";
    }

    system("pause");
}

// all Functions for Admin below

void deleteData() {
    system("clear");

    // Open file pointers
    fstream fin, fout;

    // Open the existing file
    fin.open("data.csv", ios::in);
    if (!fin.is_open()) {
        cerr << "Error: Could not open data.csv for reading.\n";
        return;
    }

    // Create a new file to store the non-deleted data
    fout.open("datanew.csv", ios::out);
    if (!fout.is_open()) {
        cerr << "Error: Could not create datanew.csv for writing.\n";
        fin.close();
        return;
    }

    string rollnum, roll1; // Changed to string
    int count = 0;
    string line, word; // Declare word here
    vector<string> row;

    // Get the roll number to decide the data to be deleted
    cout << "Enter the roll number of the record to be deleted: ";
    cin >> rollnum;

    // Check if this record exists and write others to new file
    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);

        // Read the line into the row vector
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        // Ensure the row has elements before accessing
        if (!row.empty()) {
            if (row.size() < 1) {
                cerr << "Invalid row format: " << line << "\n";
                continue; // Skip invalid rows
            }

            roll1 = row[0]; // Get the roll number as a string

            // Write to the new file if it's not the record to delete
            if (roll1 != rollnum) {
                fout << line << "\n"; // Write the whole line
            } else {
                count = 1; // Mark that we found the record
            }
        }
    }

    if (count == 1) {
        cout << "Record deleted\n";
    } else {
        cout << "Record not found\n";
    }

    // Close the file pointers
    fin.close();
    fout.close();

    // Remove the existing file
    remove("data.csv");

    // Rename the new file with the existing file name
    rename("datanew.csv", "data.csv");

   sleep(2);

    adminFunction(); // Return to admin function
}/*
void updateData() {
    system("clear");
    cout << "In update function\n";

    // File pointer
    fstream fin, fout;

    // Open an existing record
    fin.open("data.csv", ios::in);
    if (!fin.is_open()) {
        cerr << "Error opening data.csv for reading.\n";
        return;
    }

    // Create a new file to store updated data
    fout.open("datanew.csv", ios::out);
    if (!fout.is_open()) {
        cerr << "Error creating datanew.csv for writing.\n";
        return;
    }

    int rollnum, roll1, index;
    string new_marks;
    char sub;
    string line;
    vector<string> row;

    // Get the roll number from the user
    cout << "Enter the roll number of the record to be updated: ";
    cin >> rollnum;

    // Get the data to be updated
    cout << "Enter the first letter of the fields (N/G/B/A/P/C/M): ";
    cin >> sub;

    // Determine the index of the subject
    if (sub == 'n' || sub == 'N') index = 1;
    else if (sub == 'g' || sub == 'G') index = 2;
    else if (sub == 'b' || sub == 'B') index = 3;
    else if (sub == 'a' || sub == 'A') index = 4;
    else if (sub == 'p' || sub == 'P') index = 5;
    else if (sub == 'c' || sub == 'C') index = 6;
    else if (sub == 'm' || sub == 'M') index = 7;
    else {
        cout << "Wrong choice. Enter again.\n";
        fin.close();
        fout.close();
        return; // Exit the function
    }

    // Get the new marks
    cout << "Enter new Detail: ";
    cin >> new_marks;

    bool recordFound = false;

    // Traverse the file
    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);
        string word;

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        if (row.size() < 8) {
            cerr << "Invalid record format.\n";
            continue; // Skip malformed records
        }

        try {
            roll1 = stoi(row[0]); // Convert roll number from string to int
        } catch (const invalid_argument& e) {
            cerr << "Invalid roll number format: " << row[0] << "\n";
            continue; // Skip this record if the format is invalid
        }

        if (roll1 == rollnum) {
            recordFound = true;
            row[index] = new_marks; // Update the subject

            // Write the updated record
            for (size_t i = 0; i < row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row.back() << "\n"; // Last element without extra comma
        } else {
            // Write the existing record
            for (size_t i = 0; i < row.size() - 1; i++) {
                fout << row[i] << ",";
            }
            fout << row.back() << "\n"; // Last element without extra comma
        }
    }

    if (!recordFound) {
        cout << "Record not found.\n";
    }

    fin.close();
    fout.close();

    // Removing the existing file
    remove("data.csv");

    // Renaming the updated file with the existing file name
    rename("datanew.csv", "data.csv");
}

*/

void addData()
{
    system("clear");
    fstream file("data.csv", ios::out | ios::app);
    if (!file)
    {
        cout << "\nFailed to open data.csv / data.csv file not found!";
    }

    else
        cout << "\t|Enter Data|" << endl
             << endl;

    string rollNumber, name, college, branch, attendance, contact, address, grade;
    string moreData;

    cout << "\nEnter Student's roll Number : ";
    cin >> rollNumber;
    file << "\n"
         << rollNumber << ", ";

    cout << "\nEnter Studnet's Name : ";
    cin >> name;
    file << name << ", ";

    cout << "\nEnter College : ";
    cin >> college;
    file << college << ", ";

    cout << "\nEnter Branch : ";
    cin >> branch;
    file << branch << ", ";

    cout << "\nEnter Attendance : ";
    cin >> attendance;
    file << attendance << ", ";

    cout << "\nEnter Contact No. : ";
    cin >> contact;
    file << contact << ", ";

    cout << "\nEnter Address : ";
    cin >> address;
    file << address << ", ";

    cout << "\nEnter Grade : ";
    cin >> grade;
    file << grade;

    file.close();

    cout << "\nAdd more Record? (Y / N) : ";

    cin >> moreData;
    if (moreData == "y" || moreData == "Y" || moreData == "yes" || moreData == "Yes")
    {
        addData();
    }
    else if (moreData == "n" || moreData == "N" || moreData == "no" || moreData == "No")
        adminFunction();

    else
        cout << "\nEnter a valid option";

    adminFunction();
}

void viewData()
{
    system("clear");

    fstream file("data.csv");

    if (!file)
    {
        cout << "fail in opening the file";
    }
    cout << "\n\t\t\t\t\t\t|Students Record| \n\n";

    cout << "\n---------------------------------------------------------------------------------------------------------------------------------\n"
         << endl
         << endl;
   cout << left << setw(10) << "Roll" 
         << setw(20) << "Name" 
         << setw(20) << "College" 
         << setw(15) << "Branch" 
         << setw(15) << "Attendance" 
         << setw(20) << "Contact" 
         << setw(20) << "Address" 
         << setw(15) << "Grade" << endl;
 cout << "\n---------------------------------------------------------------------------------------------------------------------------------\n"
         << endl
         << endl;
    string rollNumber, name, college, branch, attendance, contact, address, grade;

    while (!file.eof()) // file.eof() = detects as how long the f
    {
        getline(file, rollNumber, ',');
        getline(file, name, ',');
        getline(file, college, ',');
        getline(file, branch, ',');
        getline(file, attendance, ',');
        getline(file, contact, ',');
        getline(file, address, ',');
        getline(file, grade, '\n');

        cout << left << setw(10) << rollNumber
             << setw(20) << name
             << setw(20) << college
             << setw(15) << branch
             << setw(15) << attendance
             << setw(20) << contact
             << setw(20) << address
             << setw(15) << grade << endl;
    }

    cout << "\n---------------------------------------------------------------------------------------------------------------------------------" << endl;
    file.close();

    cout << "\n\n 1. Add Record\n";
    cout << " 2. Delete Record\n";
    cout << " 3. Update Record\n";
    cout << " 5. Main Menu\n";
    cout << " 6. Exit\n";
    cout << "\nEnter choice : ";
    // adminFunction();
}

void adminVerification()
{
    system("clear");

    string password;

    cout << "\n\n\n\n\n\t\t\t\t\t";
    cout << "\n\n\n\t\t\t\t\tEnter Password : ";

    do
    {
        cin >> password;

        if (password != "project")
        {
            system("clear");
            cout << "\n\n\n\n\n\t\t"
                 << "wrong password!, try again or type 'menu' to Navigate to Main Menu";
            cout << "\n\n\n\t\t\t\t\tEnter Password : ";
        }

        if (password == "Menu" || password == "menu" || password == "MENU")
        {
            mainMenu();
        }

    }

    while (password != "project");
    adminFunction(); // main menu function is in the Header File adminFunction.h
}

void studentFunction()
{

    system("clear");

    fstream file("data.csv");

    if (!file)
    {
        cout << "fail in opening the file";
    }
    cout << "\n\t\t\t\t\t\t|Students Record| \n\n";

    cout << "\n---------------------------------------------------------------------------------------------------------------------------------\n"
         << endl
         << endl;
    cout << left << setw(10) << "Roll" 
         << setw(20) << "Name" 
         << setw(20) << "College" 
         << setw(15) << "Branch" 
         << setw(15) << "Attendance" 
         << setw(20) << "Contact" 
         << setw(20) << "Address" 
         << setw(15) << "Grade" << endl;
 cout << "\n---------------------------------------------------------------------------------------------------------------------------------\n"
         << endl
         << endl;
    string rollNumber, name, college, branch, attendance, contact, address, grade;

    while (!file.eof()) // file.eof() = detects as how long the f
    {
        getline(file, rollNumber, ',');
        getline(file, name, ',');
        getline(file, college, ',');
        getline(file, branch, ',');
        getline(file, attendance, ',');
        getline(file, contact, ',');
        getline(file, address, ',');
        getline(file, grade, '\n');

 cout << left << setw(10) << rollNumber
             << setw(20) << name
             << setw(20) << college
             << setw(15) << branch
             << setw(15) << attendance
             << setw(20) << contact
             << setw(20) << address
             << setw(15) << grade << endl;
    }
    cout << "\n---------------------------------------------------------------------------------------------------------------------------------" << endl;
    file.close();
    cout << "\n\n 5. Main Menu\n";
    cout << " 6. Exit\n";
    int option;
    cout << "\nEnter choice : ";

	 do
    {
        cin >> option;

        {
            switch (option)
            { 
		case 5:
                mainMenu();
                break;

            case 6:
                system("clear");
                cout << "\t\t\n\n\n\n\n\n\n\t\t\t\t\tQuitting The Program...";
		cout << "\t\t\n\n\n\n\n\n";
                for (int i = 0; i < 1; i++)
                {

                    sleep(1);
                   
                }
                exit(0);
                break;

            default:
                system("clear");
                mainMenu();
	 }
        }

    }  while (option != '6');
      // adminFunction();
}
