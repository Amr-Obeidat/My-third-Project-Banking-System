#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;
#include "Amr.h";

using namespace Amr;

//------------------------ Structs ------------------------
struct stClientInfo {
    string AccountNumber = "";
    string PhoneNumber = "";
    string Name = "";
    float AccountBalance = 0;
    string PinCode = "";
};
struct stUserInfo {
    string Name = "";
    string Password = "";
    unsigned int Permission = 0;
};

//======================== Forward Declarations ========================
// Conditions
bool IsFirstUser();
bool CheckIfClientExistByAccountNumber(string AccountNumber);
bool CheckIfUserExistByUserName(string UserName);
bool HasPermission(const stUserInfo& user, int permissionBit);

// Input / Read 
string ReadPinCode();
unsigned int ReadPermissions();
string ReadAccountNumber();
string ReadUserName();
stClientInfo ReadClientInfo();
stUserInfo ReadUserInfo(bool isFirstUser);

// Print 
void PrintClientData(const stClientInfo& Info);
void PrintUserDate(const stUserInfo& Info);
void PrintAllClientData(const vector<stClientInfo> AllClients);
void PrintAllUserInfo(const vector<stUserInfo>& AllUsers);
void PrintSearchCLientWindow();
void PrindDeleteClinetWindow();
void PrintUpdatingWindow();
void PrintAddClientWindow();
void PrintAddUserWindow();
void PrintDeleteUserWindow();
void PrintUpdateUserWindow();
void PrintSearchingUserWindow();
void PrintDenyingScreen();

// File operations
string ClinetDataInOneLine(const stClientInfo& Info, string Separator = "*//*");
vector<string> Split(string& DatainOneLine, string Seperator = "*//*");
stClientInfo OrganizeClientTheData(string& DatainOneLine);
stUserInfo OrganizeUserDate(string& DateInOneLine);
void AddClientToFile(string DataInOneLine, string FileName = "Client.txt");
vector<stClientInfo> ExtractClientsDataFromFile(string FileName = "Client.txt");
void AddAllClientsToFile(const vector<stClientInfo>& AllClients, string FileName = "Client.txt");
void AddAllUsersToFile(const vector<stUserInfo>& AllUsers, string FileName = "User.txt");
string UserDataInOneLine(const stUserInfo& User, string Separator = "*//*");
void AddUserToFile(string UserDateInOneLine, string Filename = "User.txt");
vector<stUserInfo> ExtractUserDataFromFile(string FileName = "User.txt");

// Searching
stClientInfo ReturnTheClient(string AccountNumber);
stUserInfo ReturnTheUser(string UserName);
void SearchForClientByAccountNumber();
void SearchUserByUserName();

// Deleting
void ProceedToDeletClientInfo(string AccountNumber);
void DeleteClientInfo();
void ProceedToDeleteUser(const string& UserName);
void DeleteUser();

// Updating
void UpdateClientInformations(stClientInfo& Info);
void ProceedToUpdateClientInfo(string AccountNumber);
void UpdateClientInfo();
void UpdateUserInfo(stUserInfo& User);
void ProceedToUpdateUser(const string& UserName);
void UpdateUser();

// Adding
void AddClients();
void AddUser();

// Transactions
void DepositTheMoney(string AccountNumber, float DepositAmount);
void ProceedToDeposit(string AccountNumber);
void Deposit();
void WithDrawlTheMoney(string AccountNumber, float& WithDrawAmount);
void ProccedToWithDrawl(string AccountNumber);
void WithDrawl();
float GetTotalBalances();
void PrintTotalBalnces();

// Transformations (between clients)
stClientInfo GetSourceClient(string ClientAccountNumber);
stClientInfo GetDestinationClient(string AccountNumber);
void DoTheTransformation(stClientInfo& SourceClient, stClientInfo& DestinationClient, float Amount = 0);
void ValidTransformationsInfo(stClientInfo& SourceClient, stClientInfo& DestinationClient);
void Transformations();

// Transaction menu
enum enTransactions { enDeposit = 1, enWithDrawl = 2, enTotalBalances = 3, enTransmission, enMainMenu = 5 };
enTransactions ReadTransactionType();
void TransactionHeader();
void StartTransaction();

// User management menu
enum enUserOPerations { enListUsers = 1, enAddNewUser = 2, enDeleteUser = 3, enUpdateUser = 4, enSearchUser = 5, enUserMainMenu = 6 };
enUserOPerations ReadUserOperaion();
void UserScreen();
void UserMangmentScreen();
stUserInfo Login();

// Main process menu
enum enProcess { enAddClient = 1, enDeleteClient = 2, enSearchClient = 3, enUpdateClientInfo = 4, enPrintAllClientsData = 5, enTransaction = 6, enManageUsers = 7, enLogOut = 8, enExit = 9 };
enProcess ReadProcessType();
void EndScreen();
void TheStartHeader();
void StartTheProgram(stUserInfo& CurrentUser);

// High level
bool CheckIfUserExistByUserName(string UserName);
void Start();

//------------------------ Implementations ------------------------

//------------------------ Conditions ------------------------
bool IsFirstUser() {
    fstream file("User.txt", ios::in);
    return !file.is_open() || file.peek() == EOF; // file empty or missing
}

bool CheckIfClientExistByAccountNumber(string AccountNumber) {
    vector<stClientInfo> AllClientInfo = ExtractClientsDataFromFile();
    for (auto& Client : AllClientInfo)
        if (Client.AccountNumber == AccountNumber) return true;
    return false;
}

bool CheckIfUserExistByUserName(string UserName) {
    vector<stUserInfo>AllUserInfo = ExtractUserDataFromFile();
    for (auto& User : AllUserInfo) {
        if (User.Name == UserName) {
            return true;
        }
    }
    return false;

}

bool HasPermission(const  stUserInfo &User,int BitPermission) {
    return (User.Permission & (1 << BitPermission)) != 0;
}


//------------------------ Input Functions ------------------------
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
unsigned int ReadPermissions() {
    unsigned int permissions = 0;
    string permissionNames[7] = {
        "Add Client",
        "Delete Client",
        "Search Client",
        "Update Client Info",
        "Print All Clients Data",
        "Transaction",
        "Manage Users"
    };
    
    char choice;

    cout << "Do you want to give the user all permissions (y/n): ";
    cin >> choice;
    choice = tolower(choice);

    if (choice == 'y') {
        cout << "All permissions were given to the user.\n";
        return 0x7F;
    }

    for (int i = 0; i < 7; i++) {
        while (true) {
            cout << "Do you want to give permission to " << permissionNames[i] << " (y/n): ";
            cin >> choice;
            choice = tolower(choice);

            if (choice == 'y') {
                permissions |= (1 << i); // set the i-th bit
                break;
            }
            else if (choice == 'n') {
                break;
            }
            else {
                cout << "Invalid input. Please enter 'y' or 'n'.\n";
            }
        }
    }

    return permissions;
}
string ReadAccountNumber() {
    string st = ReadString("Enter the account number: ");
    while (CheckIfClientExistByAccountNumber(st)) {
        cout << "\aAccount Number already exists! Enter another one: \n";
        st = ReadString("Enter the account number: ");
    }
    return st;
}
string ReadUserName() {
    string st = ReadString("Enter the user name : ");
    while (CheckIfUserExistByUserName(st)) {
        cout << "\aUser Name already exists! Enter another one: \n";
        st = ReadString("Enter the User Name: ");
    }
    return st;
}
stClientInfo ReadClientInfo() {
    stClientInfo Info;
    Info.AccountNumber = ReadAccountNumber();
    Info.Name = ReadString("Enter the client name : ");
    Info.PinCode = ReadPinCode();
    Info.PhoneNumber = ReadString("Enter the client phone number : ");
    Info.AccountBalance = ReadNumber("Enter the client balance : ");
    return Info;
}
stUserInfo ReadUserInfo(bool isFirstUser) {
    stUserInfo User;
    User.Name = ReadUserName();
    User.Password = ReadString("Enter the password: ");

    if (isFirstUser) {
        cout << "First user is an admin. Full permissions granted automatically.\n";
        User.Permission = 127;
    }
    else {
        User.Permission = ReadPermissions();
    }

    return User;
}


//------------------------ Print Functions ------------------------
void PrintClientData(const stClientInfo& Info) {
    cout << "Those are the Client Data : \n";
    PrintLines(40);
    cout << left << setw(20) << "Account Number:" << Info.AccountNumber << "\n";
    cout << left << setw(20) << "Name:" << Info.Name << "\n";
    cout << left << setw(20) << "Pin Code:" << Info.PinCode << "\n";
    cout << left << setw(20) << "Phone Number:" << Info.PhoneNumber << "\n";
    cout << left << setw(20) << "Account Balance:" << Info.AccountBalance << "\n";
    PrintLines(40);
    cout << "\n";
}
void PrintUserDate(const stUserInfo& Info) {
    cout << "Those are the User Data : \n";
    PrintLines(40);
    cout << left << setw(20) << "User Name:" << Info.Name << "\n";
    cout << left << setw(20) << "Password:" << Info.Password << "\n";
    cout << left << setw(20) << "Permissions:" << Info.Permission << "\n";
    PrintLines(40);
    cout << "\n";
}
void PrintAllClientData(const vector<stClientInfo> AllClients) {
    if (AllClients.empty()) {
        cout << "\aThere are currently no clients to display. \n";
        return;
    }

    const int width = 80;
    string Header = "Client List (" + to_string(AllClients.size()) + ") Client(s)";
    PrintLines(width);
    PrintMiddle(Header, width);
    PrintLines(width);

    cout << "|" << setw(15) << left << "Account Number"
        << "|" << setw(20) << left << "Name"
        << "|" << setw(10) << left << "Pin code"
        << "|" << setw(15) << left << "Phone Number"
        << "|" << setw(15) << right << "Account Balance"
        << "|\n";
    PrintLines(width);

    for (const stClientInfo& Client : AllClients) {
        cout << "|" << setw(15) << left << Client.AccountNumber
            << "|" << setw(20) << left << Client.Name
            << "|" << setw(10) << left << Client.PinCode
            << "|" << setw(15) << left << Client.PhoneNumber
            << "|" << setw(15) << left << fixed << setprecision(2) << Client.AccountBalance
            << "|\n";
    }

    PrintLines(width);
    cout << "\n";
}
void PrintAllUserInfo(const vector<stUserInfo>& AllUsers) {
    if (AllUsers.empty()) {
        cout << "\aThere are currently no users to display. \n";
        return;
    }
    const int Width = 80;
    PrintLines(Width);
    string Header = "User List (" + to_string(AllUsers.size()) + ") User(s)";
    PrintMiddle(Header, Width);
    PrintLines(Width);
    cout << "|" << setw(20) << left << "User Name " << "|" << setw(15) << left << "User Password " << "|" << setw(5) << "User Permissions";
    cout << "\n";
    PrintLines(Width);
    for (auto& User : AllUsers) {
        cout << "|" << setw(20) << left << User.Name << "|" << setw(15) << left << User.Password << "|" << setw(5) << User.Permission << "\n";

    }
    PrintLines(Width);
    cout << "\n";



}
void PrintSearchCLientWindow() {
    PrintLines(50);
    PrintMiddle("Searching Client Window", 50);
    PrintLines(50);
    cout << "\n";
}
void PrindDeleteClinetWindow() {
    PrintLines(50);
    PrintMiddle("Deleting Client Information Window", 50);
    PrintLines(50);
    cout << "\n";
}
void PrintUpdatingWindow() {
    PrintLines(50);
    PrintMiddle("Updating Client Information Window", 50);
    PrintLines(50);
    cout << "\n";
}
void PrintAddClientWindow() {
    PrintLines(50);
    PrintMiddle("Adding Clients Window", 50);
    PrintLines(50);
    cout << "\n";
}
void PrintAddUserWindow() {
    PrintLines(50);
    PrintMiddle("Adding User Window ", 50);
    PrintLines(50);
    cout << "\n";
}
void PrintDeleteUserWindow() {

    PrintLines(50);
    PrintMiddle("Deleting User Window ", 50);
    PrintLines(50);
    cout << "\n";
}
void PrintUpdateUserWindow() {
    PrintLines(50);
    PrintMiddle("Updating User Window ", 50);
    PrintLines(50);
    cout << "\n";
}
void PrintSearchingUserWindow() {
    PrintLines(50);
    PrintMiddle("Searching User Window ", 50);
    PrintLines(50);
    cout << "\n";

}
void PrintDenyingScreen() {
    PrintLines(50);
    cout << "\aAccess Denied,\n";
    cout << "You Dont Have Permission to do this",
        cout << " \nPlease Contact The Admin \n";
    PrintLines(50);
    cout << "\n";
   


}
//------------------------ File Operations ------------------------
string ClinetDataInOneLine(const stClientInfo& Info, string Separator) {
    string Line = "";
    Line += Info.AccountNumber + Separator;
    Line += Info.Name + Separator;
    Line += Info.PinCode + Separator;
    Line += Info.PhoneNumber + Separator;
    Line += to_string(Info.AccountBalance);
    return Line;
}
vector<string> Split(string& DatainOneLine, string Seperator) {
    int pos = 0;
    vector<string> OrganizedData;
    string word = "";
    while ((pos = DatainOneLine.find(Seperator)) != std::string::npos) {
        word = DatainOneLine.substr(0, pos);
        if (!word.empty())
            OrganizedData.push_back(word);
        DatainOneLine.erase(0, pos + Seperator.size());
    }
    if (!DatainOneLine.empty())
        OrganizedData.push_back(DatainOneLine);
    return OrganizedData;
}
stClientInfo OrganizeClientTheData(string& DatainOneLine) {
    vector<string> OrganizedData = Split(DatainOneLine);
    stClientInfo Info;
    if (OrganizedData.size() < 5)
        return Info;
    Info.AccountNumber = OrganizedData[0];
    Info.Name = OrganizedData[1];
    Info.PinCode = OrganizedData[2];
    Info.PhoneNumber = OrganizedData[3];
    Info.AccountBalance = stof(OrganizedData[4]);
    return Info;
}
stUserInfo OrganizeUserDate(string& DateInOneLine) {
    vector<string>OrganizedDate = Split(DateInOneLine);
    stUserInfo Info;
    if (OrganizedDate.size() < 3) {
        return Info;
    }
    Info.Name = OrganizedDate[0];
    Info.Password = OrganizedDate[1];
    Info.Permission = stoi(OrganizedDate[2]);
    return Info;

}
void AddClientToFile(string DataInOneLine, string FileName) {
    fstream MyFile(FileName, ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << DataInOneLine << "\n";
        MyFile.close();
    }
}
vector<stClientInfo> ExtractClientsDataFromFile(string FileName) {
    vector<stClientInfo> AllClientsInfo;
    fstream MyFile(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (Line.empty()) continue;
            AllClientsInfo.push_back(OrganizeClientTheData(Line));

        }
        MyFile.close();
    }
    return AllClientsInfo;
}
void AddAllClientsToFile(const vector<stClientInfo>& AllClients, string FileName) {
    fstream MyFile(FileName, ios::out);
    if (MyFile.is_open()) {
        for (auto& Client : AllClients) {
            MyFile << ClinetDataInOneLine(Client) << "\n";
        }
        MyFile.close();
    }
}
void AddAllUsersToFile(const vector<stUserInfo>& AllUsers, string FileName) {
    fstream MyFile(FileName, ios::out);
    if (MyFile.is_open()) {
        for (auto& User : AllUsers) {
            MyFile << UserDataInOneLine(User) << "\n";
        }
        MyFile.close();
    }
}
string UserDataInOneLine(const stUserInfo& User, string Separator) {
    string UserData = "";
    UserData += User.Name + Separator;
    UserData += User.Password + Separator;
    UserData += to_string(User.Permission);
    return UserData;

}
void AddUserToFile(string UserDateInOneLine, string Filename) {

    fstream MyFile;
    MyFile.open(Filename, ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << UserDateInOneLine << "\n";
        MyFile.close();
    }
}
vector<stUserInfo>ExtractUserDataFromFile(string FileName) {
    fstream MyFile;
    vector <stUserInfo> AllUserInfo;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (Line.empty())continue;
            AllUserInfo.push_back((OrganizeUserDate(Line)));

        }
        MyFile.close();
    }
    return AllUserInfo;



}

//------------------------ Searching ------------------------
stClientInfo ReturnTheClient(string AccountNumber) {
    vector<stClientInfo> AllClientInfo = ExtractClientsDataFromFile();
    for (auto& Client : AllClientInfo)
        if (Client.AccountNumber == AccountNumber) return Client;
    return stClientInfo{};
}
stUserInfo ReturnTheUser(string UserName) {
    vector<stUserInfo>AllUserInfo = ExtractUserDataFromFile();
    for (auto& User : AllUserInfo) {
        if (User.Name == UserName) {
            return User;
        }
    }
    return stUserInfo{};
}
void SearchForClientByAccountNumber() {
    PrintSearchCLientWindow();

    string AccountNumber = ReadString("Enter the client account number : ");
    if (CheckIfClientExistByAccountNumber(AccountNumber))
        PrintClientData(ReturnTheClient(AccountNumber));
    else
        cout << "Client with (" << AccountNumber << ") account number was not found : \n";
}
void SearchUserByUserName() {
    PrintSearchingUserWindow();
    string UserName = ReadString("Enter the User Name  : ");
    if (CheckIfUserExistByUserName(UserName))
        PrintUserDate(ReturnTheUser(UserName));
    else
        cout << "User with (" << UserName << ") account number was not found : \n";
}
//------------------------ Deleting ------------------------
void ProceedToDeletClientInfo(string AccountNumber) {
    vector<stClientInfo> AllClients = ExtractClientsDataFromFile();
    for (auto it = AllClients.begin(); it != AllClients.end();) {
        if (it->AccountNumber == AccountNumber) {
            AllClients.erase(it);
            break;
        }
        else it++;
    }
    AddAllClientsToFile(AllClients);
}

void DeleteClientInfo() {
    PrindDeleteClinetWindow();

    string ClientAccountNumber = ReadString("\nEnter the client account number you wish to delete : ");
    if (CheckIfClientExistByAccountNumber(ClientAccountNumber)) {
        PrintClientData(ReturnTheClient(ClientAccountNumber));
        cout << "Are you sure you want to delete this user(y/n) !\n";
        char condition; cin >> condition;
        if (condition == 'y' || condition == 'Y') {
            ProceedToDeletClientInfo(ClientAccountNumber);
            cout << "\nClient deleted successfully.\n";
        }
        else cout << "The Deletion was cancelled\n";
    }
    else cout << "\aUser with (" << ClientAccountNumber << ") AccountNumber was not found \n";
}
void ProceedToDeleteUser(const string& UserName) {
    vector<stUserInfo> AllUsers = ExtractUserDataFromFile();
    for (auto it = AllUsers.begin(); it != AllUsers.end();) {
        if (it->Name == UserName) {
            AllUsers.erase(it);
            break;
        }
        else it++;
    }
    AddAllUsersToFile(AllUsers);
}
void DeleteUser() {
    PrintDeleteUserWindow();
    string UserName = ReadString("Enter the user name you wish to delete: ");
    if (CheckIfUserExistByUserName(UserName)) {
        stUserInfo User = ReturnTheUser(UserName);
        cout << "User Name: " << User.Name << "\n";
        cout << "Are you sure you want to delete this user (y/n)? ";
        char condition; cin >> condition;
        if (condition == 'y' || condition == 'Y') {
            ProceedToDeleteUser(UserName);
            cout << "\nUser deleted successfully.\n";
        }
        else cout << "The deletion was cancelled.\n";
    }
    else cout << "\aUser not found.\n";
}

//------------------------ Updating ------------------------
void UpdateClientInformations(stClientInfo& Info) {
    Info.Name = ReadString("Enter the client name : ");
    Info.PinCode = ReadPinCode();
    Info.PhoneNumber = ReadString("Enter the client phone number : ");
    Info.AccountBalance = ReadNumber("Enter the client balance : ");
}

void ProceedToUpdateClientInfo(string AccountNumber) {
    vector<stClientInfo> AllClients = ExtractClientsDataFromFile();
    for (auto& Client : AllClients) {
        if (Client.AccountNumber == AccountNumber) {
            UpdateClientInformations(Client);
            break;
        }
    }
    AddAllClientsToFile(AllClients);
}

void UpdateClientInfo() {
    PrintUpdatingWindow();

    string ClientAccountNumber = ReadString("Enter the client account number : ");
    if (CheckIfClientExistByAccountNumber(ClientAccountNumber)) {
        PrintClientData(ReturnTheClient(ClientAccountNumber));
        cout << "\nAre you sure you want to update client info(y/n) : ";
        char condition; cin >> condition;
        if (condition == 'Y' || condition == 'y') {
            ProceedToUpdateClientInfo(ClientAccountNumber);
            cout << "\nClient Info was updated successfully : ";
        }
        else cout << "The Updating Operation was cancelled\n";
    }
    else cout << "Client with (" << ClientAccountNumber << ") account number was not found : \n";
}
void UpdateUserInfo(stUserInfo& User) {
    User.Name = ReadString("Enter new user name: ");
    User.Password = ReadString("Enter new password: ");
    User.Permission = ReadPermissions();
}
void ProceedToUpdateUser(const string& UserName) {
    vector<stUserInfo> AllUsers = ExtractUserDataFromFile();
    for (auto& user : AllUsers) {
        if (user.Name == UserName) {
            UpdateUserInfo(user);
            break;
        }
    }
    fstream MyFile("User.txt", ios::out);
    for (const auto& user : AllUsers)
        MyFile << UserDataInOneLine(user) << "\n";
    MyFile.close();
}
void UpdateUser() {
    PrintUpdateUserWindow();
    string UserName = ReadString("Enter the user name to update: ");
    if (CheckIfUserExistByUserName(UserName)) {
        stUserInfo User = ReturnTheUser(UserName);
        cout << "User Name: " << User.Name << "\n";
        cout << "Are you sure you want to update this user (y/n)? ";
        char condition; cin >> condition;
        if (condition == 'y' || condition == 'Y') {
            ProceedToUpdateUser(UserName);
            cout << "\nUser info updated successfully.\n";
        }
        else cout << "The updating operation was cancelled.\n";
    }
    else cout << "\aUser not found.\n";
}
//------------------------ Adding ------------------------

void AddClients() {
    PrintAddClientWindow();
    char condition = 'y';
    do {
        stClientInfo Client = ReadClientInfo();
        AddClientToFile(ClinetDataInOneLine(Client));
        cout << "\nDo you want to add another client(y/n) : ";
        cin >> condition;
    } while (condition == 'y' || condition == 'Y');
}
void AddUser() {
    PrintAddUserWindow();
    char condition = 'y';
    do {
        bool isFirst = IsFirstUser();
        stUserInfo User = ReadUserInfo(isFirst);
        AddUserToFile(UserDataInOneLine(User));
        cout << "\nDo you want to add another user(y/n) : ";
        cin >> condition;
    } while (condition == 'y' || condition == 'Y');
}
//------------------------ Transactions ------------------------
void DepositTheMoney(string AccountNumber, float DepositAmount) {
    vector<stClientInfo> AllInfo = ExtractClientsDataFromFile();
    for (auto& Client : AllInfo) {
        if (Client.AccountNumber == AccountNumber) {
            Client.AccountBalance += DepositAmount;
            break;
        }
    }
    AddAllClientsToFile(AllInfo);
}

void ProceedToDeposit(string AccountNumber) {
    float Deposit = ReadPositiveNumber("Enter the deposit amount : ");
    cout << "\nAre you sure you want to perform this transaction (y,n) : ";
    char condition; cin >> condition;
    if (condition == 'y' || condition == 'Y') {
        DepositTheMoney(AccountNumber, Deposit);
        cout << "Deposit done successfully\n";
    }
    else cout << "\nThe Deposit Operation was cancelled ";
}

void Deposit() {
    PrintLines(50);
    PrintMiddle("Deposit Window", 50);
    PrintLines(50);
    cout << "\n";

    string ClientAccountNumber = ReadString("Enter the client account number : ");
    if (CheckIfClientExistByAccountNumber(ClientAccountNumber)) {
        PrintClientData(ReturnTheClient(ClientAccountNumber));
        ProceedToDeposit(ClientAccountNumber);
    }
    else cout << "Client with (" << ClientAccountNumber << ") account number was not found : \n";
}

void WithDrawlTheMoney(string AccountNumber, float& WithDrawAmount) {
    vector<stClientInfo> AllInfo = ExtractClientsDataFromFile();
    for (auto& Client : AllInfo) {
        if (Client.AccountNumber == AccountNumber) {
            while (WithDrawAmount > Client.AccountBalance) {
                cout << "Amount Exceeded the balance, you can withdraw up to " << Client.AccountBalance << "\n";
                WithDrawAmount = ReadPositiveNumber("Enter another amount : ");
            }
            Client.AccountBalance -= WithDrawAmount;
            break;
        }
    }
    AddAllClientsToFile(AllInfo);
}

void ProccedToWithDrawl(string AccountNumber) {
    float WithDraw = ReadPositiveNumber("Enter the withdrawl amount : ");
    cout << "\nAre you sure you want to preform this transaction (y/n) : ";
    char condition; cin >> condition;
    if (condition == 'y' || condition == 'Y') {
        WithDrawlTheMoney(AccountNumber, WithDraw);
        cout << "Withdrawl completed successfully\n";
    }
    else cout << "\nThe withdrawl Operation was cancelled ";
}

void WithDrawl() {
    PrintLines(50);
    PrintMiddle("Withdraw Window", 50);
    PrintLines(50);
    cout << "\n";

    string ClientAccountNumber = ReadString("Enter the client account number : ");
    if (CheckIfClientExistByAccountNumber(ClientAccountNumber)) {
        PrintClientData(ReturnTheClient(ClientAccountNumber));
        ProccedToWithDrawl(ClientAccountNumber);
    }
    else cout << "Client with (" << ClientAccountNumber << ") account number was not found : \n";
}

float GetTotalBalances() {
    vector<stClientInfo> AllInfo = ExtractClientsDataFromFile();
    float TotalBalances = 0;
    for (auto& client : AllInfo) TotalBalances += client.AccountBalance;
    return TotalBalances;
}

void PrintTotalBalnces() {
    vector<stClientInfo> AllInfo = ExtractClientsDataFromFile();
    if (AllInfo.empty()) {
        cout << "\aThere are currently no clients to display their balances.\n";
        return;
    }
    PrintAllClientData(AllInfo);
    float TotalBalances = GetTotalBalances();
    PrintMiddle("Total Balances = " + to_string(TotalBalances), 70);
}

//------------------------ Transactions Between Clients ------------------------
stClientInfo GetSourceClient(string ClientAccountNumber) {
    if (CheckIfClientExistByAccountNumber(ClientAccountNumber))
        return ReturnTheClient(ClientAccountNumber);
    cout << "Client with (" << ClientAccountNumber << ") account number was not found : \n";
    return stClientInfo{};
}

stClientInfo GetDestinationClient(string AccountNumber) {
    if (CheckIfClientExistByAccountNumber(AccountNumber))
        return ReturnTheClient(AccountNumber);
    cout << "Client with (" << AccountNumber << ") account number was not found : \n";
    return stClientInfo{};
}

void DoTheTransformation(stClientInfo& SourceClient, stClientInfo& DestinationClient, float Amount) {
    Amount = ReadPositiveNumber("Enter the transaction amount : ");
    cout << "The Destination Account Name is " << DestinationClient.Name << "\n";
    cout << "Are you sure you want to do the transaction (y,n) :";
    char condition; cin >> condition;
    if (condition == 'y' || condition == 'Y') {
        WithDrawlTheMoney(SourceClient.AccountNumber, Amount);
        DepositTheMoney(DestinationClient.AccountNumber, Amount);
    }
    else cout << "\nThe Transaction Operation canceled.\n";
}

void ValidTransformationsInfo(stClientInfo& SourceClient, stClientInfo& DestinationClient) {
    short NumberOfTries = 3;
    string Pin;
    cout << "Enter your pin : \n";

    do {
        Pin = ReadPinCode();
        if (Pin == SourceClient.PinCode) {
            DoTheTransformation(SourceClient, DestinationClient);
            break;
        }
        NumberOfTries--;
        cout << "\a\nWrong Pin !";
        if (NumberOfTries > 0) cout << "\nYou have " << NumberOfTries << " more tries\n";
        else cout << "\nNo more tries left. Access denied!\n";
    } while (NumberOfTries > 0);
}

void Transformations() {
    PrintLines(60);
    PrintMiddle("Transaction window", 60);
    PrintLines(60);

    string SourceAccountNumber = ReadString("Enter the source client account number : ");
    if (!CheckIfClientExistByAccountNumber(SourceAccountNumber)) {
        cout << "Client with (" << SourceAccountNumber << ") account number was not found : \n";
        return;
    }
    string DestinationAccountNumber = ReadString("Enter the Destination client account number : ");
    if (!CheckIfClientExistByAccountNumber(DestinationAccountNumber)) {
        cout << "Client with (" << DestinationAccountNumber << ") account number was not found : \n";
        return;
    }

    stClientInfo SourceClient = ReturnTheClient(SourceAccountNumber);
    stClientInfo DestinationClient = ReturnTheClient(DestinationAccountNumber);

    ValidTransformationsInfo(SourceClient, DestinationClient);
}

//------------------------ Transaction Menu ------------------------
enTransactions ReadTransactionType() {
    short Transaction = ReadNumberInRange("What process do you want to proceed : ", 1, 5);
    return static_cast<enTransactions>(Transaction);
}

void TransactionHeader() {
    PrintLines2(40);
    PrintMiddle("Main Transactions Screen", 40);
    PrintLines2(40);
    cout << left;
    cout << setw(40) << "[1] :Deposit" << endl;
    cout << setw(40) << "[2] :WithDrawl" << endl;
    cout << setw(40) << "[3] :Total Balances" << endl;
    cout << setw(40) << "[4] :Transmission" << endl;
    cout << setw(40) << "[5] :Main Menu" << endl;
    PrintLines2(40);
}

void StartTransaction() {
    enTransactions TransactionType;
    do {
        system("cls");
        TransactionHeader();
        TransactionType = ReadTransactionType();
        system("cls");
        switch (TransactionType) {
        case enTransactions::enDeposit: Deposit(); break;
        case enTransactions::enWithDrawl: WithDrawl(); break;
        case enTransactions::enTotalBalances: PrintTotalBalnces(); break;
        case enTransactions::enTransmission: Transformations(); break;
        }
        if (TransactionType != enTransactions::enMainMenu) 
            system("pause");
    } while (TransactionType != enTransactions::enMainMenu);
}

//___________________________User Menu____________________________________
enUserOPerations ReadUserOperaion() {
    short OPeration = ReadNumberInRange("What process do you want to proceed : ", 1, 6);
    return static_cast<enUserOPerations>(OPeration);
}
void UserScreen() {
    PrintLines2(40);
    PrintMiddle("Manage Users Menue Screen", 40);
    PrintLines2(40);
    cout << left;
    cout << setw(40) << "[1] :List Users" << endl;
    cout << setw(40) << "[2] :Add New User" << endl;
    cout << setw(40) << "[3] :Delete User" << endl;
    cout << setw(40) << "[4] :Update User" << endl;
    cout << setw(40) << "[5] :Find User" << endl;
    cout << setw(40) << "[6] :Main Menue" << endl;
    PrintLines2(40);
}
void UserMangmentScreen() {
    enUserOPerations Operation;
    do {
        system("cls");
        UserScreen();
        Operation = ReadUserOperaion();
        system("cls");
        switch (Operation) {
        case enUserOPerations::enAddNewUser:
            AddUser(); break;
        case enUserOPerations::enDeleteUser:
            DeleteUser(); break;
        case enUserOPerations::enListUsers:
            PrintAllUserInfo(ExtractUserDataFromFile()); break;
        case enUserOPerations::enUpdateUser:
            UpdateUser(); break;
        case enUserOPerations::enSearchUser:
            SearchUserByUserName(); break;
        case enUserOPerations::enUserMainMenu:
            continue;

        }


        if (Operation != enUserOPerations::enUserMainMenu) {
            system("pause");
        }
    } while (Operation != enUserOPerations::enUserMainMenu);

}
stUserInfo Login() {
    vector<stUserInfo> AllUsers = ExtractUserDataFromFile();

    // If no users exist, create the first admin////
    if (AllUsers.empty()) {
        cout << "No users found. Creating the first admin user.\n";
        stUserInfo FirstUser = ReadUserInfo(true);
        AddUserToFile(UserDataInOneLine(FirstUser));
        return FirstUser;
    }


    while (true) {
        string UserName = ReadString("Enter your username: ");
        string Password = ReadString("Enter your password: ");

        stUserInfo User = ReturnTheUser(UserName);
        if (User.Name == UserName && User.Password == Password) {
            return User;
        }
        system("cls");
        cout << "\aInvalid username or password. Please try again.\n";
    }
}

//------------------------ Main Process Menu ------------------------
enProcess ReadProcessType() {
    short Process = ReadNumberInRange("What process do you want to proceed ", 1, 9);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return static_cast<enProcess>(Process);
}

void EndScreen() {
    PrintLines(60);
    PrintMiddle("The program has ended :)", 60);
    PrintLines(60);
}

void TheStartHeader() {
    PrintLines2(40);
    PrintMiddle("Main Menu Screen", 40);
    PrintLines2(40);
    cout << left;
    cout << setw(40) << "[1] : Add Client" << endl;
    cout << setw(40) << "[2] : Delete Client" << endl;
    cout << setw(40) << "[3] : Search Client" << endl;
    cout << setw(40) << "[4] : Update Client Info" << endl;
    cout << setw(40) << "[5] : Print All Clients Data" << endl;
    cout << setw(40) << "[6] : Transaction" << endl;
    cout << setw(40) << "[7] : Manage Users " << endl;
    cout << setw(40) << "[8] : Log out" << endl;
    cout << setw(40) << "[9] : Exit" << endl;
    PrintLines2(40);
}

void StartTheProgram(stUserInfo& CurrentUser) {

    enProcess ProcessType;
    do {
        system("cls");
        TheStartHeader();
        ProcessType = ReadProcessType();
        system("cls");

        switch (ProcessType) {
        case enProcess::enAddClient:
            if (HasPermission(CurrentUser, 0)) {
                AddClients();
            }
            else {
                PrintDenyingScreen();
            }
            break;

        case enProcess::enDeleteClient:
            if (HasPermission(CurrentUser, 1)) {
                DeleteClientInfo();
            }
            else {
                PrintDenyingScreen();
            }
            break;

        case enProcess::enUpdateClientInfo:
            if (HasPermission(CurrentUser, 3)) {
                UpdateClientInfo();
            }
            else {
                PrintDenyingScreen();
            }
            break;

        case enProcess::enPrintAllClientsData:
            if (HasPermission(CurrentUser, 4)) {
                PrintAllClientData(ExtractClientsDataFromFile());
            }
            else {
                PrintDenyingScreen();
            }
            break;

        case enProcess::enSearchClient:
            if (HasPermission(CurrentUser, 2)) {
                SearchForClientByAccountNumber();
            }
            else {
                PrintDenyingScreen();
            }
            break;

        case enProcess::enTransaction:
            if (HasPermission(CurrentUser, 5)) {
                StartTransaction();
            }
            else {
                PrintDenyingScreen();
                system("pause");
            }
            break;

        case enProcess::enManageUsers:
            if (HasPermission(CurrentUser, 6)) {
                UserMangmentScreen();
              
            }
            else {
                PrintDenyingScreen();
                system("pause");
            }
            break;

        case enProcess::enLogOut:
            Start();
            break;
        case enProcess::enExit:
            EndScreen(); 
            exit(0);     
            break;
        }

            



            if (ProcessType != enProcess::enExit && ProcessType != enProcess::enTransaction && ProcessType != enProcess::enManageUsers)
            {
                system("pause");
            }

        } while (ProcessType != enProcess::enExit);

        EndScreen();
    }

void Start() {
    stUserInfo User = Login();
    StartTheProgram(User);

}
//------------------------ Main ------------------------
int main() {

   Start();


}
