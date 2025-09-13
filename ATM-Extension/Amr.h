#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>   // for rand()
#include <cmath>
#include <vector>
#include <algorithm>
#include<iomanip>
#include <fstream>
using namespace std;

namespace Amr {

    // ============================================================
    // 📌 Input Reading Functions
    // ============================================================

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

    // Read a validated positive number with prompt
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

    // Read a validated integer within a range
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

    // Read exactly 2 floats
    void ReadTwoNumbers(float& num1, float& num2, const string& prompt1, const string& prompt2) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            break;
        }
    }

    // Read exactly 3 floats
    void ReadThreeNumbers(float& num1, float& num2, float& num3,
        const string& prompt1, const string& prompt2, const string& prompt3) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt3 << ": ";
            if (!(cin >> num3)) {
                cout << "Invalid input for " << prompt3 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            break;
        }
    }

    // Read exactly 4 floats
    void ReadFourNumbers(float& num1, float& num2, float& num3, float& num4,
        const string& prompt1, const string& prompt2, const string& prompt3, const string& prompt4) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt3 << ": ";
            if (!(cin >> num3)) {
                cout << "Invalid input for " << prompt3 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt4 << ": ";
            if (!(cin >> num4)) {
                cout << "Invalid input for " << prompt4 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            break;
        }
    }

    // Read exactly 5 floats
    void ReadFiveNumbers(float& num1, float& num2, float& num3, float& num4, float& num5,
        const string& prompt1, const string& prompt2, const string& prompt3, const string& prompt4, const string& prompt5) {
        while (true) {
            cout << prompt1 << ": ";
            if (!(cin >> num1)) {
                cout << "Invalid input for " << prompt1 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt2 << ": ";
            if (!(cin >> num2)) {
                cout << "Invalid input for " << prompt2 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt3 << ": ";
            if (!(cin >> num3)) {
                cout << "Invalid input for " << prompt3 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt4 << ": ";
            if (!(cin >> num4)) {
                cout << "Invalid input for " << prompt4 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cout << prompt5 << ": ";
            if (!(cin >> num5)) {
                cout << "Invalid input for " << prompt5 << ". Try again.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            break;
        }
    }

    string ReadString(const string& prompt) {
        cout << prompt;
        if (cin.peek() == '\n') cin.ignore();
        string st;
        getline(cin, st);
        return st;
    }

    // ============================================================
    // 📌 Utility Functions
    // ============================================================

    int RandomNumber(int From, int To) {
        if (From > To) {
            cout << "Invalid Range. Enter a valid range.\n";
            return -1;
        }
        return rand() % (To - From + 1) + From;
    }

    void ResetScreen() { system("color 07"); }

    void PrintLines(int count) {
        if (count <= 0) { cout << "(no lines to print)\n"; return; }
        for (int i = 0; i < count; ++i) cout << "-";
        cout << "\n";
    }

    void PrintLines2(int count) {
        if (count <= 0) { cout << "(no lines to print)\n"; return; }
        for (int i = 0; i < count; ++i) cout << "=";
       
        cout << "\n";
    }

    void PrintSpaces(int count) {
        if (count <= 0) return;
        for (int i = 0; i < count; ++i) cout << " ";
    }

    void PrintGreen(const string& text) {
        system("color 0A"); cout << text << endl; system("color 07");
    }

    void PrintRed(const string& text) {
        system("color 0C"); cout << text << endl; system("color 07");
    }

    void PrintYellow(const string& text) {
        system("color 0E"); cout << text << endl; system("color 07");
    }

    void PrintMiddle(string st, short width) {
        size_t LeftSide = (width - st.size()) / 2;
        size_t RightSide = (width - st.size()) - LeftSide;
        cout << string(LeftSide, ' ') << st << string(RightSide, ' ')<< "\n";;
    }

    void SetConsoleColor(string color) {
        transform(color.begin(), color.end(), color.begin(), ::tolower);
        if (color == "red") system("color 4F");
        else if (color == "green") system("color 2F");
        else if (color == "yellow") system("color 6F");
        else if (color == "white") system("color 7F");
        else if (color == "blue") system("color 1F");
        else cout << "Unsupported color!\n";
    }

    char InvertChar(char ch) {
        return isupper(ch) ? tolower(ch) : toupper(ch);
    }

    // ============================================================
    // 📌 File Handling Functions
    // ============================================================

    void SaveFile_Content_ToVector(vector<string>& vFile, string FileName) {
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open()) {
            string line;
            while (getline(MyFile, line)) {
                if (line != "") vFile.push_back(line);
            }
            MyFile.close();
        }
    }

    void SaveVector_Content_ToFile(vector<string>& vFile, string FileName) {
        fstream MyFile;
        MyFile.open(FileName, ios::out);
        if (MyFile.is_open()) {
            for (string& line : vFile) MyFile << line << "\n";
        }
        MyFile.close();
    }

    void Delete_File_Content(vector<string>& vFile, string Item, string FileName) {
        for (string& line : vFile) if (line == Item) line = "";
        SaveVector_Content_ToFile(vFile, FileName);
    }

    void Update_File_Content(vector<string>& vFile, string TheItem, string TheItemRplacment, string FileName) {
        for (string& line : vFile) if (line == TheItem) line = TheItemRplacment;
        SaveVector_Content_ToFile(vFile, FileName);
    }

    void PrintFile_Content(string FileName) {
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        if (MyFile.is_open()) {
            string line;
            while (getline(MyFile, line)) cout << line << " ";
            MyFile.close();
        }
    }



// ============================================================
    //                  Date & Day Utilities
    // ============================================================

    enum enDayOfWeek { Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

    // --------------------- Struct ---------------------
    struct StDate {
        int Day;
        int Month;
        int Year;

        // Optional weekday info
        int DayIndex = -1;
        enDayOfWeek DayOfWeek;
        string DayName;
    };

    // --------------------- Basic Utilities ---------------------
    bool LeapYear(int Year) {
        return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
    }

    int DaysInMonth(int Month, int Year) {
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (Month < 1 || Month > 12) return 0;
        if (Month == 2 && LeapYear(Year)) return 29;
        return days[Month - 1];
    }

    bool IsLastMonthInYear(int Month) { return Month == 12; }
    bool IsLastDayInMonth(StDate Info) { return Info.Day == DaysInMonth(Info.Month, Info.Year); }

    // --------------------- Weekday Utilities ---------------------
    short GetDayOfWeekIndex(int year, int month, int day) {
        short a = (14 - month) / 12;
        short y = year - a;
        short m = month + 12 * a - 2;
        return (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
    }
    string DayOfWeekToString(short day) {
        enDayOfWeek Day = static_cast<enDayOfWeek>(day);
        switch (day) {
        case Sunday: return "Sunday";
        case Monday: return "Monday";
        case Tuesday: return "Tuesday";
        case Wednesday: return "Wednesday";
        case Thursday: return "Thursday";
        case Friday: return "Friday";
        case Saturday: return "Saturday";
        default: return "Invalid";
        }
    }
    string GetTheDayName(StDate Date) {
        short index = GetDayOfWeekIndex(Date.Year, Date.Month, Date.Day);
        string DayeName = DayOfWeekToString(index);
        return DayeName;
    }
   
    // --------------------- Input / Output ---------------------
    StDate ReadDate() {
        StDate Info;
        Info.Year = ReadPositiveNumber("Enter the year :");
        Info.Month = ReadNumberInRange("Enter the month : ", 1, 12);
        Info.Day = ReadNumberInRange("Enter the day", 1, DaysInMonth(Info.Month, Info.Year));
      
        return Info;
    }

    void PrintDateInfo(StDate Info) {
        cout << Info.Day << "/" << Info.Month << "/" << Info.Year << "\n";
       /* cout << "Day Index: " << Info.DayIndex << "\n";
        cout << "Day Name: " << Info.DayName << "\n";*/
    }

    // --------------------- Current Date ---------------------
    StDate GetCurrentDate() {
        StDate Current;
        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);

        Current.Year = localTime.tm_year + 1900;
        Current.Month = localTime.tm_mon + 1;
        Current.Day = localTime.tm_mday;
       
        return Current;
    }

    // --------------------- Add / Subtract Days ---------------------
    StDate AddDays(StDate Info, int DaysToAdd) {
        int RemainingDays = Info.Day + DaysToAdd;
        while (RemainingDays > (LeapYear(Info.Year) ? 366 : 365)) {
            RemainingDays -= (LeapYear(Info.Year) ? 366 : 365);
            Info.Year++;
        }
        while (RemainingDays > DaysInMonth(Info.Month, Info.Year)) {
            RemainingDays -= DaysInMonth(Info.Month, Info.Year);
            Info.Month++;
            if (Info.Month > 12) {
                Info.Month = 1;
                Info.Year++;
            }
        }
        Info.Day = RemainingDays;
       
        return Info;
    }

    StDate SubtractDays(StDate Info, int DaysToSub) {
        int RemainingDays = Info.Day - DaysToSub;
        while (RemainingDays <= -(LeapYear(Info.Year) ? 366 : 365)) {
            RemainingDays += (LeapYear(Info.Year) ? 366 : 365);
            Info.Year--;
        }
        while (RemainingDays <= 0) {
            Info.Month--;
            if (Info.Month < 1) {
                Info.Month = 12;
                Info.Year--;
            }
            RemainingDays += DaysInMonth(Info.Month, Info.Year);
        }
        Info.Day = RemainingDays;
     
        return Info;
    }

    // --------------------- Add / Subtract Helper Wrappers ---------------------
    StDate Add_X_Days(StDate Date, int Days) { return AddDays(Date, Days); }
    StDate Add_X_Weeks(StDate Date, int Weeks) { return AddDays(Date, Weeks * 7); }
    StDate AddOneMonth(StDate Date) {
        if (IsLastMonthInYear(Date.Month)) { Date.Year++; Date.Month = 1; }
        else Date.Month++;
        if (Date.Day > DaysInMonth(Date.Month, Date.Year)) Date.Day = DaysInMonth(Date.Month, Date.Year);
       
        return Date;
    }
    StDate Add_X_Months(StDate Date, int Months) { while (Months--) Date = AddOneMonth(Date); return Date; }
    StDate Add_X_Year(StDate Date, int Years) { Date.Year += Years; return Date; }
    StDate Add_X_Decades(StDate Date, int Decades) { return Add_X_Year(Date, Decades * 10); }
    StDate Add_X_Century(StDate Date, int Centuries) { return Add_X_Year(Date, Centuries * 100); }
    StDate Add_X_Millennium(StDate Date, int Millennia) { return Add_X_Year(Date, Millennia * 1000); }

    StDate Subtract_X_Days(StDate Date, int Days) { return SubtractDays(Date, Days); }
    StDate Subtract_X_Weeks(StDate Date, int Weeks) { return SubtractDays(Date, Weeks * 7); }
    StDate SubtractOneMonth(StDate Date) {
        Date.Month--;
        if (Date.Month < 1) { Date.Month = 12; Date.Year--; }
        if (Date.Day > DaysInMonth(Date.Month, Date.Year)) Date.Day = DaysInMonth(Date.Month, Date.Year);
      
        return Date;
    }
    StDate Subtract_X_Months(StDate Date, int Months) { while (Months--) Date = SubtractOneMonth(Date); return Date; }
    StDate Subtract_X_Year(StDate Date, int Years) { Date.Year -= Years;  return Date; }
    StDate Subtract_X_Decades(StDate Date, int Decades) { return Subtract_X_Year(Date, Decades * 10); }
    StDate Subtract_X_Century(StDate Date, int Centuries) { return Subtract_X_Year(Date, Centuries * 100); }
    StDate Subtract_X_Millennium(StDate Date, int Millennia) { return Subtract_X_Year(Date, Millennia * 1000); }

    // --------------------- Date Difference / Age ---------------------
    long long CountDays_From_Ref_ToGivenDate(StDate Date) {
        int years = Date.Year - 1;
        long long AllDays = years * 365LL;
        int LeapDays = (years / 4) - (years / 100) + (years / 400);
        AllDays += LeapDays;
        for (int i = 1; i < Date.Month; i++) AllDays += DaysInMonth(i, Date.Year);
        AllDays += Date.Day;
        return AllDays;
    }

    int Diff_BetweenDates(StDate Date1, StDate Date2, bool IncludeEndDay = false) {
        long long d1 = CountDays_From_Ref_ToGivenDate(Date1);
        long long d2 = CountDays_From_Ref_ToGivenDate(Date2);
        long long diff = abs(d2 - d1);
        return IncludeEndDay ? diff + 1 : diff;
    }
  
    int GetAgeInDays(StDate BirthDate, StDate CurrentDate) { return Diff_BetweenDates(BirthDate, CurrentDate); }




/////////////////////////////////////////////////// Print month Calender;
enum enMonth {
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12
};
enMonth ReadMonth() {
    int number = ReadNumberInRange("Enter the month ", 1, 12);
    return(static_cast<enMonth>(number));
}
string GetTheMonthName(enMonth Month) {
    switch (Month) {
    case January:   return "January";
    case February:  return "February";
    case March:     return "March";
    case April:     return "April";
    case May:       return "May";
    case June:      return "June";
    case July:      return "July";
    case August:    return "August";
    case September: return "September";
    case October:   return "October";
    case November:  return "November";
    case December:  return "December";

    }
}
void  PrintMonthHeader(string MonthName) {
    cout << "===========================" << MonthName << "===========================\n";

}
void PrintMonthCalendar(short year, short month) {
    PrintMonthHeader(GetTheMonthName(static_cast<enMonth>(month)));
    short MaxDays = DaysInMonth(month, year);
    short position = GetDayOfWeekIndex(year, month, 1);
    string Days[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    for (int i = 0; i < 7; i++) {
        cout << setw(4) << Days[i];

    }
    cout << "\n";
    for (int i = 0; i < position; i++) {
        cout << setw(4) << " ";
    }

    for (int i = 1; i <= MaxDays; i++) {
        cout << setw(4) << i;
        if ((i + position) % 7 == 0) {
            cout << "\n";
        }
    }

}
/////////////////////////////////////////////////// Print month  Calender;

/////////////////////// Print year  Calender;
void PrintCalenderYear(short Year) {
    PrintLines(40);
    string x = "Calender-" + to_string(Year);
    PrintMiddle(x, 40);
    PrintLines(40);
    for (int i = 1; i <= 12; i++) {
        PrintMonthCalendar(Year, i);
        cout << "\n";
    }
}
/////////////////////// Print year  Calender;

// ==================NumberToText============================//
string NumberToText(long long number) {

    string Ones[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                 "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
                 "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
    string Tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty",
            "Sixty", "Seventy", "Eighty", "Ninety" };
    if (number == 0) {
        return " ";
    }
    if (number >= 1 && number <= 19) {
        return Ones[number];;
    }
    if (number > 19 && number <= 99) {

        return Tens[number / 10] + " " + NumberToText(number % 10);

    }
    if (number >= 100 && number <= 999) {
        return Ones[number / 100] + " Hundred " + NumberToText(number % 100);

    }
    if (number >= 1000 && number <= 999999)

        return NumberToText(number / 1000) + " Thousand " + NumberToText(number % 1000);
    if (number >= 1000000 && number <= 999999999) {
        return NumberToText(number / 1000000) + " Million " + NumberToText(number % 1000000);
    }

    if (number >= 1000000000 && number <= 999999999999)
        return NumberToText(number / 1000000000) + " Billion " + NumberToText(number % 1000000000);

    if (number >= 1000000000000 && number <= 9999999999999LL) {
        return NumberToText(number / 1000000000000) + " Trillion " + NumberToText(number % 1000000000000);
    }
    return "";
}
// ==================NumberToText============================//


}
