#pragma once


#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>  // for rand()
#include <cmath>
#include<vector>
#include <algorithm>
#include<fstream>
using namespace std;




namespace Amr {

    // --------------- Input Reading Functions ---------------

// Read a validated float with prompt
    float ReadNumber(const string& prompt) {
        float number;
        cout << prompt;
        while (!(cin >> number)) {
            cout << "Invalid input. " << prompt;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return number;
    }

    // Read a validated float without prompt
    float ReadUserNumber() {
        float number;
        while (!(cin >> number)) {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return number;
    }

    // Read a validated positive integer with prompt



    float ReadPositiveNumber(const string& prompt) {
        float number;
        cout << prompt;
        while (!(cin >> number) || number < 0) {
            cout << "Invalid input. Enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return number;
    }

    // Read a validated integer within a range with prompt
    int ReadNumberInRange(const string& message, int from, int to) {
        int number;
        cout << message << " [" << from << " - " << to << "]: ";
        while (!(cin >> number) || number < from || number > to) {
            cout << "Invalid input. Enter a number between " << from << " and " << to << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return number;
    }

    // Read exactly 2 floats with prompt for each
    void ReadTwoNumbers(float& num1, float& num2, const string& prompt1, const string& prompt2) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }
    }

    // Read exactly 3 floats with prompt for each
    void ReadThreeNumbers(float& num1, float& num2, float& num3,
        const string& prompt1, const string& prompt2, const string& prompt3) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt3 << ": ";
            if (!(cin >> num3)) {
                cout << "Invalid input for " << prompt3 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }
    }

    // Read exactly 4 floats with prompt for each
    void ReadFourNumbers(float& num1, float& num2, float& num3, float& num4,
        const string& prompt1, const string& prompt2, const string& prompt3, const string& prompt4) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt3 << ": ";
            if (!(cin >> num3)) {
                cout << "Invalid input for " << prompt3 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt4 << ": ";
            if (!(cin >> num4)) {
                cout << "Invalid input for " << prompt4 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }
    }

    // Read exactly 5 floats with prompt for each
    void ReadFiveNumbers(float& num1, float& num2, float& num3, float& num4, float& num5,
        const string& prompt1, const string& prompt2, const string& prompt3, const string& prompt4, const string& prompt5) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt3 << ": ";
            if (!(cin >> num3)) {
                cout << "Invalid input for " << prompt3 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt4 << ": ";
            if (!(cin >> num4)) {
                cout << "Invalid input for " << prompt4 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << prompt5 << ": ";
            if (!(cin >> num5)) {
                cout << "Invalid input for " << prompt5 << ". Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        }
    }

    // --------------- Utility Functions ---------------

    // Generate a random number between From and To (inclusive) with validation
    int RandomNumber(int From, int To) {
        if (From > To) {
            cout << "Invalid Range. Enter a valid range.\n";
            return -1;
        }
        return rand() % (To - From + 1) + From;
    }

    // Reset console screen color to default
    void ResetScreen() {
        system("color 07");
    }

    // Print 'count' lines of '-' with validation
    void PrintLines(int count) {
        if (count <= 0) {
            cout << "(no lines to print)\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            cout << "-";
        }
        cout << endl;
    }
    void PrintLines2(int count) {
        if (count <= 0) {
            cout << "(no lines to print)\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            cout << "=";
        }
        cout << endl;
    
    }

    // Print 'count' spaces with validation
    void PrintSpaces(int count) {
        if (count <= 0) return;
        for (int i = 0; i < count; ++i) {
            cout << " ";
        }
    }

    // Print text in green color (Windows console)
    void PrintGreen(const string& text) {
        system("color 0A"); // Green text on black bg
        cout << text << endl;
        system("color 07"); // Reset to default
    }

    // Print text in red color (Windows console)
    void PrintRed(const string& text) {
        system("color 0C"); // Red text on black bg
        cout << text << endl;
        system("color 07"); // Reset to default
    }

    // Print text in yellow color (Windows console)
    void PrintYellow(const string& text) {
        system("color 0E"); // Yellow text on black bg
        cout << text << endl;
        system("color 07"); // Reset to default
    }



    void PrintMiddle(string st, short width) {
        size_t LeftSide = (width - st.size() )/2;
        size_t RightSide = (width - st.size()) - LeftSide;

        cout << string(LeftSide, ' ') << st << string(RightSide, ' ')<<"\n";

    }

    void SetConsoleColor(string color) {
        // Convert color string to lowercase for case-insensitive comparison
        transform(color.begin(), color.end(), color.begin(), ::tolower);

        if (color == "red")
            system("color 4F"); // Red background, white text
        else if (color == "green")
            system("color 2F"); // Green background, white text
        else if (color == "yellow")
            system("color 6F"); // Yellow background, white text
        else if (color == "white")
            system("color 7F"); // Default white background and text
        else if (color == "blue")
            system("color 1F"); // Blue background, white text
        else
            cout << "Unsupported color!\n";
    }


    //////////////////// fstream fun
    void SaveFile_Content_ToVector(vector<string>& vFile, string FileName) {
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open()) {
            string line;
            while (getline(MyFile, line)) {
                if (line != "") {
                    vFile.push_back(line);
                }
            }



            MyFile.close();
        }

    }
    void SaveVector_Content_ToFile(vector<string>& vFile, string FileName) {
        fstream MyFile;
        MyFile.open(FileName, ios::out);
        if (MyFile.is_open()) {

            for (string& line : vFile) {
                MyFile << line << "\n";
            }
        }
        MyFile.close();
    }
    void Delete_File_Content(vector<string>& vFile, string Item, string FileName) {

        for (string& line : vFile) {
            if (line == Item) {
                line = "";
            }
        }
        SaveVector_Content_ToFile(vFile, FileName);


    }
    void Update_File_Content(vector<string>& vFile, string TheItem, string TheItemRplacment, string FileName) {
        for (string& line : vFile) {
            if (line == TheItem) {
                line = TheItemRplacment;

            }
        }
        SaveVector_Content_ToFile(vFile, FileName);
    }
    void PrintFile_Content(string FileName) {
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open()) {
            string line;
            while (getline(MyFile, line)) {
                cout << line << " ";
            }
            MyFile.close();
        }
    }


    /////// invert char 
    char  InvertChar(char ch) {
        return isupper(ch) ? tolower(ch) : toupper(ch);
    }

    /////// read string 
    string ReadString(const string& prompt) {
        cout << prompt;


        if (cin.peek() == '\n') cin.ignore();

        string st;
        getline(cin, st);
        return st;
    }







}