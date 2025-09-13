#include <iostream>
#include "Amr.h"
#include <string>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;
using namespace Amr;

//------------------------ Structs ------------------------
struct stClient {
    string AccountNumber = "";
    string PhoneNumber = "";
    string Name = "";
    float AccountBalance = 0;
    string PinCode = "";
};

//------------------------ Utility Functions ------------------------
vector<string> Split(string DataInOneLine, string Seperator = "*//*") {
    int pos = 0;
    string word = "";
    vector<string> OrganizedData;
    while ((pos = DataInOneLine.find(Seperator)) != string::npos) {
        word = DataInOneLine.substr(0, pos);
        if (!word.empty()) OrganizedData.push_back(word);
        DataInOneLine.erase(0, pos + Seperator.size());
    }
    if (!DataInOneLine.empty()) OrganizedData.push_back(DataInOneLine);
    return OrganizedData;
}

string ClientDataInOneLine(const stClient& Client, string Seperator = "*//*") {
    string Data = "";
    Data += Client.AccountNumber + Seperator;
    Data += Client.Name + Seperator;
    Data += Client.PinCode + Seperator;
    Data += Client.PhoneNumber + Seperator;
    Data += to_string(Client.AccountBalance);
    return Data;
}

stClient OrganizeClinetDate(const string& DataInOneLine) {
    vector<string> OrganizedData = Split(DataInOneLine);
    stClient Info;
    if (OrganizedData.size() < 5) return Info;
    Info.AccountNumber = OrganizedData[0];
    Info.Name = OrganizedData[1];
    Info.PinCode = OrganizedData[2];
    Info.PhoneNumber = OrganizedData[3];
    Info.AccountBalance = stof(OrganizedData[4]);
    return Info;
}

//------------------------ File I/O Functions ------------------------
vector<stClient> ExtractClientsData(const string FileName = "C:\\Users\\PC\\source\\repos\\Banking System\\Banking System\\Client.txt") {
    fstream MyFile;
    vector<stClient> AllData;

    MyFile.open(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (Line.empty()) continue;
            AllData.push_back(OrganizeClinetDate(Line));
        }
        MyFile.close();
    }
    else {
        cout << "Cant Open the file ~";
    }
    return AllData;
}

stClient ReturnClient(string ClientAccountNumber) {
    vector<stClient> AllClients = ExtractClientsData();
    for (auto& Client : AllClients) {
        if (Client.AccountNumber == ClientAccountNumber) return Client;
    }
    return {}; 
}

void SaveClientsDataToFile(const vector<stClient>& AllClients, const string FileName = "C:\\Users\\PC\\source\\repos\\Banking System\\Banking System\\Client.txt") {
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open()) {
        for (auto& Client : AllClients) {
            MyFile << ClientDataInOneLine(Client) << "\n";
        }
        MyFile.close();
    }
}

//------------------------ Enum ------------------------
enum class QuickWithdraw : short {
    W20 = 1,
    W50,
    W100,
    W200,
    W400,
    W600,
    W800,
    W1000,
    Exit
};
//////////////////////////////////////
void Start();
//------------------------ User Input ------------------------
short ReadUserQuickWithDrawChoice() {
    short number = ReadNumberInRange("Choose What to withdraw : ", 1, 9);
    
    return number;
}
string ReadPinCode() {
    string PinCode;
    while (true) {
        PinCode = ReadString("Enter the PIN (4 digits): ");
        if (PinCode.length() == 4 && all_of(PinCode.begin(), PinCode.end(), ::isdigit)) {
            break;
        }
        cout << "Invalid PIN! It must be exactly 4 digits.\n";
    }
    return PinCode;
}

//------------------------ Core Logic Functions ------------------------
int WithDrawlAmount(QuickWithdraw choice) {
    switch (choice) {
    case QuickWithdraw::W20: return 20;
    case QuickWithdraw::W50: return 50;
    case QuickWithdraw::W100: return 100;
    case QuickWithdraw::W200: return 200;
    case QuickWithdraw::W400: return 400;
    case QuickWithdraw::W600: return 600;
    case QuickWithdraw::W800: return 800;
    case QuickWithdraw::W1000: return 1000;
    case QuickWithdraw::Exit: return 0;
    default: return 0;
    }
}

void WithDraw(short WithDrawAmount, stClient& Client) {
    vector<stClient> AllClients = ExtractClientsData();
    Client.AccountBalance -= WithDrawAmount;
    for (auto& C : AllClients) {
        if (C.AccountNumber == Client.AccountNumber) {
            C.AccountBalance = Client.AccountBalance;
            break;
        }
    }

    SaveClientsDataToFile(AllClients);
}
void Deposit(int DepoistAmount, stClient& Client) {
    vector<stClient>AllData = ExtractClientsData();
    for (auto& C : AllData) {
        if (C.AccountNumber == Client.AccountNumber) {
            Client.AccountBalance+= DepoistAmount;
            C.AccountBalance += DepoistAmount;
            break;
        }
    }
    SaveClientsDataToFile(AllData);
}
//------------------------ UI/Print Functions ------------------------
void PrintBalnaceScreen() {
    PrintLines2(40);
    PrintMiddle("Balance Screen ", 40);
    PrintLines2(40);
}

void PrintBalance(stClient Client) {
    cout << "Your Balance is " << Client.AccountBalance << "\n";
}

void PrintQuickwithDrawWindow() {
    PrintLines2(40);
    PrintMiddle("Quick Withdraw Screen ", 40);
    PrintLines2(40);
}

void QuickWithDrawHeader() {
    PrintQuickwithDrawWindow();
    cout << left;
    cout << "    " << setw(12) << "[1] 20" << setw(12) << "[2] 50" << "\n";
    cout << "    " << setw(12) << "[3] 100" << setw(12) << "[4] 200" << "\n";
    cout << "    " << setw(12) << "[5] 400" << setw(12) << "[6] 600" << "\n";
    cout << "    " << setw(12) << "[7] 800" << setw(12) << "[8] 1000" << "\n";
    cout << "    " << setw(12) << "[9] Exit" << "\n";
    PrintLines2(40);
}
void DepositScreen() {
    PrintLines2(40);
    PrintMiddle("Deposit Screen ", 40);
    PrintLines2(40);
}
void LogInScreen() {
    PrintLines2(40);
    PrintMiddle("Log In Screen ", 40);
    PrintLines2(40);
}
void PrintStartScreen() {
    PrintLines2(50);
    PrintMiddle("ATM Main Menu Screen", 50);
    PrintLines2(50);

    cout << left;
    cout << "    " << setw(25) << "[1] Quick Withdraw" << "\n";
    cout << "    " << setw(25) << "[2] Normal Withdraw" << "\n";
    cout << "    " << setw(25) << "[3] Deposit" << "\n";
    cout << "    " << setw(25) << "[4] Check Balance" << "\n";
    cout << "    " << setw(25) << "[5] Log Out" << "\n";

    PrintLines2(50);
}
void PrintNormalWithDrawScreen() {
    PrintLines2(40);
    PrintMiddle("Normal WithDraw Screen", 40);
    PrintLines2(40);
}


//------------------------ Quick Withdraw Operation ------------------------
void QuickWithDrawOperation(stClient& Client) {
    QuickWithDrawHeader();

    short choiceNum = ReadUserQuickWithDrawChoice();
    if (choiceNum == 9) {
        return;
    }
    QuickWithdraw choice = static_cast<QuickWithdraw>(choiceNum);
    short WithDrawAmountVal = WithDrawlAmount(choice);
    while (WithDrawAmountVal > Client.AccountBalance) {
        cout << "\aYou exceeded your balance limit. You can withdraw up to "
            << Client.AccountBalance << "\n";

        // Ask user again
        short choiceNum = ReadUserQuickWithDrawChoice();
        QuickWithdraw choice = static_cast<QuickWithdraw>(choiceNum);
        WithDrawAmountVal = WithDrawlAmount(choice);
    }
    cout << "Are you sure you want to perform this operation (y/n) : ";
    char cond;
    cin >> cond;
    while (cond != 'y' && cond != 'n') {
        cout << "\aWrong Input! Enter (y) or (n): ";
        cin >> cond;
        cond = tolower(cond);
    }
    if(cond=='y'||cond=='Y')
    
    {
        WithDraw(WithDrawAmountVal, Client);
    }
    else {
        cout << "The Operations was cancelled \n";
    }
    
}

//------------------------ Quick Withdraw Operation ------------------------
int  ReadNormalWithDrawl() {
    int Amount = ReadPositiveNumber("Enter an amount  which  is a multiple of 5 : ");
    while (Amount % 5 != 0) {
       Amount= ReadPositiveNumber("\aEnter an amount  which  is a multiple of 5 : ");

    }
    return Amount;
}
void NormalWithDrawlOperation( stClient &Client) {
    PrintNormalWithDrawScreen();
    int Amount = ReadNormalWithDrawl();
    while (Amount > Client.AccountBalance) {
        cout << "\aYou exceeded your balance limit. You can withdraw up to "
            << Client.AccountBalance << "\n";
        Amount = ReadNormalWithDrawl();
    }
    cout << "Are you sure you want to perform this operation (y/n) ";
    char cond;
    cin >> cond;
    while (cond != 'y' && cond != 'n') {
        cout << "\aWrong Input! Enter (y) or (n): ";
        cin >> cond;
        cond = tolower(cond);
    }
    if(cond=='Y'||cond=='y')
    {
        WithDraw(Amount, Client);
    }
    else {
        cout << "The Operations was cancelled \n";
    }

}
//------------------------ Deposit ------------------------
int ReadDepositAmount() {
    int DepositAMount = ReadPositiveNumber("Enter the deposit amount : ");
    return DepositAMount;
 }
void DepositOperation(stClient &client) {
    DepositScreen();
    int Amount = ReadDepositAmount();
    cout << "Are you sure you want to perform this operation (y/n) : ";
    char cond;
    cin >> cond;
    while (cond != 'y' && cond != 'n') {
        cout << "\aWrong Input! Enter (y) or (n): ";
        cin >> cond;
        cond = tolower(cond);
    }
    if(cond=='Y'||cond=='y')
 
    {
        Deposit(Amount, client);
        
    }
    else {
        cout << "The Operation was cancelled \n";
    }
}
//------------------------ Login ------------------------
stClient LogIn() {
    LogInScreen();
   while(true)
   {
      
       string AccountNumber = ReadString("Enter your account number : ");
       stClient Client = ReturnClient(AccountNumber);
       string Pin = ReadPinCode();
       if (Pin == Client.PinCode) {
           return Client;
       }
       else {
           system("cls");
           LogInScreen();
           cout << "Invalid User Name Or Pin Code\a \n";
       }
   }
}
//------------------------ Start ------------------------
enum enOperations { QuickWithDraw = 1, NormalWithDraw = 2, Depost = 3, CheckBalance = 4, LogOut = 5 };;
enOperations ReadOperation() {
    short Op = ReadNumberInRange("Enter the operation you want to do : ",1,5);
    return static_cast<enOperations>(Op);

}

void StartTheProgramm(stClient& Client) {
    enOperations Operation;

    do {
        system("cls"); 
        PrintStartScreen();
        Operation = ReadOperation(); 
        system("cls");
        switch (Operation) {
        case enOperations::QuickWithDraw:
            QuickWithDrawOperation(Client);
            break;

        case enOperations::NormalWithDraw:
            NormalWithDrawlOperation(Client);
            break;

        case enOperations::Depost:
            DepositOperation(Client);
            break;

        case enOperations::CheckBalance:
            PrintBalnaceScreen();
            PrintBalance(Client);
            break;

        case enOperations::LogOut:
            Start();

       
        }

        
        if (Operation != enOperations::LogOut) {
        
            system("pause");
   
        }

    } while (Operation != enOperations::LogOut);
}
void Start() {
    stClient Client = LogIn();
    StartTheProgramm(Client);
}
int main() {
    Start();

}
