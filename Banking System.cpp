
#include <iostream>
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib> 
#include <cmath>
#include<vector>
#include<iomanip>
#include <algorithm>
#include<fstream>
using namespace std;
#include"Amr.h";




using namespace Amr;
struct stClientInfo {
    string AccountNumber="";
    string PhoneNumber="";
    string Name="";
    float AccountBalance=0;
    string  PinCode="";





};
bool CheckIfClientExistByAccountNumber(string AccountNumber);
///////////////////// read pin
string ReadPinCode() {
    string PinCode;
    while (true) {
        PinCode = ReadString("Enter the PIN (4 digits): ");

        // Check length and ensure all characters are digits
        if (PinCode.length() == 4 && all_of(PinCode.begin(), PinCode.end(), ::isdigit)) {
            break; // valid PIN
        }
        cout << "Invalid PIN! It must be exactly 4 digits.\n";
    }
    return PinCode;
}
string ReadAccountNumber() {
    string st = ReadString("Enter the account number: ");

    while (CheckIfClientExistByAccountNumber(st)) {
        cout << "\aAccount Number already exists! Enter another one: \n";
        st = ReadString("Enter the account number: ");
    }

    return st;
}

///////////////////// read pin
stClientInfo  ReadClientInfo() {
    stClientInfo Info;
    Info.AccountNumber=ReadAccountNumber();

    Info.Name = ReadString("Enter the client name : ");
    Info.PinCode = ReadPinCode();
    Info.PhoneNumber = ReadString("Enter the client phone number : ");
    Info.AccountBalance = ReadNumber("Enter the client balance : ");
    return Info;


}

 
//////////Print Functions////////////
void PrintAllClientData(const vector<stClientInfo> AllClients ) {
    
    if (AllClients.size() == 0) {
        cout << "\aThere are currently no clients to display. \n";
    }

    else
    {
        const int width = 80;
        string Header = "Client List (" + to_string(AllClients.size()) + ") Client(s)";

        // Print top border
        PrintLines(width);

        // Print centered header
        PrintMiddle(Header, width);
        // Print header separator
        PrintLines(width);

        // Column titles
        cout << "|" << setw(15) << left << "Account Number"
            << "|" << setw(20) << left << "Name"
            << "|" << setw(10) << left << "Pin code"
            << "|" << setw(15) << left << "Phone Number"
            << "|" << setw(15) << right << "Account Balance"
            << "|\n";

        PrintLines(width);

        // Data rows
        for (const stClientInfo& Client : AllClients) {
            cout << "|" << setw(15) << left << Client.AccountNumber
                << "|" << setw(20) << left << Client.Name
                << "|" << setw(10) << left << Client.PinCode
                << "|" << setw(15) << left << Client.PhoneNumber
                << "|" << setw(15) << left << fixed << setprecision(2) << Client.AccountBalance
                << "|\n";
        }

        // Bottom border
        PrintLines(width);
        cout << "\n";
    }
}


void PrintClientData(const stClientInfo& Info) {
    cout << "Those are the Client Data : \n";

    PrintLines(40); // top border

    cout << left << setw(20) << "Account Number:" << Info.AccountNumber << "\n";
    cout << left << setw(20) << "Name:" << Info.Name << "\n";
    cout << left << setw(20) << "Pin Code:" << Info.PinCode << "\n";
    cout << left << setw(20) << "Phone Number:" << Info.PhoneNumber << "\n";
    cout << left << setw(20) << "Account Balance:" << Info.AccountBalance << "\n";

    PrintLines(40); // bottom border
    cout << "\n";
}
//////////Print Functions////////////
  

 
///////////Adding And Extracting Cleints/////////////
string ClinetDataInOneLine(const stClientInfo& Info, string Separator = "*//*") {
    ////////////////// To Save Data As Lines in the file
    string Line = "";
    Line += Info.AccountNumber + Separator;
    Line += Info.Name + Separator;
    Line += (Info.PinCode) + Separator;
    Line += Info.PhoneNumber + Separator;
    Line += to_string(Info.AccountBalance);  
    return Line;



}
vector<string> Split(string& DatainOneLine, string Seperator = "*//*") {
    ////////// To Recover Data from the file after being Unreadable To Organized way in vector
    int pos = 0;
    vector<string>OrganizedData;
    string word = "";
    while ((pos = DatainOneLine.find(Seperator)) != std::string::npos) {
        word = DatainOneLine.substr(0, pos);
        if (!word.empty()) {
            OrganizedData.push_back(word);
        }
        DatainOneLine.erase(0, pos + Seperator.size());
    }
    if (!DatainOneLine.empty()) {
        OrganizedData.push_back(DatainOneLine);
    }
    return OrganizedData;




}
stClientInfo OrganizeTheData(string& DatainOneLine) {
    vector<string> OrganizedData = Split(DatainOneLine);
    stClientInfo Info;

    if (OrganizedData.size() < 5) {
        // File is empty or line is invalid
        return Info; // return an empty client safely
    }

    Info.AccountNumber = OrganizedData[0];
    Info.Name = OrganizedData[1];
    Info.PinCode = OrganizedData[2];
    Info.PhoneNumber = OrganizedData[3];
    Info.AccountBalance = stof(OrganizedData[4]);
    return Info;
}
void AddClientToFile(string DataInOneLine,string FileName="Client.txt") {

    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open()) {

        MyFile << DataInOneLine << "\n";
        MyFile.close();
    }


}
vector<stClientInfo> ExtractClientsDataFromFile(string FileName = "Client.txt") {

    stClientInfo Client;
    vector<stClientInfo>AllClientsInfo;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        while (getline(MyFile, Line)) {
            if (Line.empty()) continue; // skip blank lines
            Client = OrganizeTheData(Line);
            AllClientsInfo.push_back(Client);
        }
        MyFile.close();



    }




    return AllClientsInfo;


}
void AddAllClientsToFile(const vector<stClientInfo>& AllClients, string FileName = "Client.txt") {

    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open()) {
        for ( auto &CLient : AllClients) {
            string Line = ClinetDataInOneLine(CLient);
            MyFile << Line << "\n";



        }
        MyFile.close();

    }




}
///////////Adding And Extacting Cleints/////////////



//////////////// search
bool CheckIfClientExistByAccountNumber(string AccountNumber) {
    vector<stClientInfo>AllClientInfo=ExtractClientsDataFromFile();
    for (stClientInfo& Client : AllClientInfo) {
        if (Client.AccountNumber == AccountNumber) {
            return true;
        }
    }
    return false;
}
stClientInfo ReturnTheClient(string AccountNumber) {
    vector<stClientInfo>AllClientInfo = ExtractClientsDataFromFile();
   
    for (stClientInfo& Client : AllClientInfo) {
        if (Client.AccountNumber == AccountNumber) {
            return Client;
        }
    }
    return stClientInfo{};
}
void  SearchForClientByAccountNumber() {
    PrintLines(50);
    PrintMiddle("Searching Client  Window", 50);
    PrintLines(50);
    cout << "\n";
    string AccountNumber = ReadString("Enter the client account number : ");
    bool found = CheckIfClientExistByAccountNumber(AccountNumber);
    if (found) {
     stClientInfo TheClient=   ReturnTheClient(AccountNumber);
        PrintClientData(TheClient);
            
    }
    else {
        cout << "CLient with (" << AccountNumber << ") account number was not found : \n";
    }
    
 }
//////////////// search

/////////////////Deleting Client Info/////////////
void ProceedToDeletClientInfo(string AccountNumber) {
   vector<stClientInfo>AllClients=ExtractClientsDataFromFile();
   for (auto it = AllClients.begin(); it != AllClients.end(); ) {
       if (it->AccountNumber == AccountNumber) {
           AllClients.erase(it);
           break;
       }
       else {
           it++;
       }
   }
     
   AddAllClientsToFile(AllClients);

}
void DeleteClientInfo() {
    PrintLines(50);
    PrintMiddle("Deleting Client Information Window", 50);
    PrintLines(50);
    cout << "\n";
    string ClientAccountNumber = ReadString("\nEnter the client account number you wish to delete : ");

 bool Found=   CheckIfClientExistByAccountNumber(ClientAccountNumber);
 if (Found) {
     PrintClientData(ReturnTheClient(ClientAccountNumber));

     cout << "Are you sure you want to delete this user(y/n) !\n";
     char condition;
     cin >> condition;
     if(condition=='y'||condition=='Y')
     {
         ProceedToDeletClientInfo(ClientAccountNumber);
         cout << "\nClient deleted successfully.\n";
     }
     else {
         cout << "The Deletion was cancelled\n";
     }
 }
 else {
     cout << "\aUser with (" << ClientAccountNumber << ") AccountNumber was not found \n";
 }

}
/////////////////Deleting Client Info/////////////

////////// Update File Contant
void UpdateClientInformations(stClientInfo& Info) {
    Info.Name = ReadString("Enter the client name : ");
    Info.PinCode = ReadPinCode();
    Info.PhoneNumber = ReadString("Enter the client phone number : ");
    Info.AccountBalance = ReadNumber("Enter the client balance : ");
  

}
void  ProceedToUpdateClientInfo(string AccountNumber) {
    stClientInfo Client = ReturnTheClient(AccountNumber);
    vector<stClientInfo>AllCLients = ExtractClientsDataFromFile();
    for (auto it = AllCLients.begin(); it != AllCLients.end();) {
        if (it->AccountNumber == AccountNumber) {
            UpdateClientInformations(*it);
            break;
        }
        else {
            it++;
        }
    }
    AddAllClientsToFile(AllCLients);
}
void UpdateClientInfo() {
    PrintLines(50);
    PrintMiddle("Updating Client Information Window",50);
    PrintLines(50);
    cout << "\n";
    string ClientAccountNumber = ReadString("Enter the client account number : ");
    bool Found = CheckIfClientExistByAccountNumber(ClientAccountNumber);
   
    if (Found) {
        PrintClientData(ReturnTheClient(ClientAccountNumber));

        cout << "\nAre you sure you want to update client info(y/n) : ";
        char condition;
        cin >> condition;
        if (condition == 'Y' || condition == 'y') {
            ProceedToUpdateClientInfo(ClientAccountNumber);

            cout << "\n Client Info was updated successful : ";

        }
        else {
            cout << "The Updating Operation was cancelled\n";
        }
    }
        else {
            cout << "CLient with (" << ClientAccountNumber << ") account number was not found : \n";

        }



    }
////////// Update File Contant




////////////// Add Clients////////
void AddClients() {
    PrintLines(50);
    PrintMiddle("Adding Clients  Window", 50);
    PrintLines(50);
    cout << "\n";
    char condition = 'y';         

    do {
            
        stClientInfo Client;
        Client = ReadClientInfo();
        AddClientToFile(ClinetDataInOneLine(Client));
        cout << "\nDo you want to add another clients(y/n) : ";
        cin >> condition;

    } while (condition == 'y' || condition == 'Y');







}
////////////// Add Clients////////



////////////////////////////////////////////////////////////////////////// Transaction menu

/////////////////// Deposit
void DepositTheMoney(string AccountNumber, float DepositAmount) {
    vector<stClientInfo>AllInfo = ExtractClientsDataFromFile();
    for (auto it = AllInfo.begin(); it != AllInfo.end();) {
        if (it->AccountNumber == AccountNumber) {
            (it->AccountBalance) += DepositAmount;
            break;
        }
        else {
            it++;
        }
    }
    AddAllClientsToFile(AllInfo);
}
void ProceedToDeposit( string accountnumber) {
    float Deposit = ReadPositiveNumber("Enter the deposit amount : ");
    cout << "\nAre you sure you want to perform this transaction (y,n) : ";
    char condition = ' ';
    cin >> condition;
    if (condition == 'y' || condition == 'Y') {
        DepositTheMoney(accountnumber, Deposit);
        cout << "Deposit done successfully\n";

    }
    else {
        cout << "\nThe Deposit Operation was cancelled ";
    }





}
void Deposit() {
    PrintLines(50);
    PrintMiddle("Deposit window ", 50);
    PrintLines(50);
    cout << "\n";

    string ClientAccountNumber = ReadString("Enter the client account number : ");
    bool found = CheckIfClientExistByAccountNumber(ClientAccountNumber);
    if (found) {
        PrintClientData(ReturnTheClient(ClientAccountNumber));
        
        ProceedToDeposit(ClientAccountNumber);



    }
    else {
        cout << "CLient with (" << ClientAccountNumber << ") account number was not found : \n";
    }









}
/////////////////// Deposit

///////////////withdraw
void WithDrawlTheMoney(string accounnumber, float  &WithDrawlAmount) {
    vector<stClientInfo>AllInfo = ExtractClientsDataFromFile();
    for (auto it = AllInfo.begin(); it != AllInfo.end();) {
        if (it->AccountNumber == accounnumber) {
            while (WithDrawlAmount > it->AccountBalance)

            {
                cout << "Amount Exceeded the balance ,you can withdraw up to " << it->AccountBalance << "\n";

                WithDrawlAmount = ReadPositiveNumber("Enter another amount : ");
            }
            it->AccountBalance -= WithDrawlAmount;
            break;
        }
        else {
            it++;
        }
    }


        AddAllClientsToFile(AllInfo);
    


}
void ProccedToWithDrawl(string AccountNumber) {
    float  WithDraw = ReadPositiveNumber("Enter the withdrawl amount : ");
    cout << "\nAre you sure you want to preform this transaction (y/n) : ";
    char condition = ' ';
    cin >> condition;
    if (condition == 'y' || condition == 'Y') {
        WithDrawlTheMoney(AccountNumber, WithDraw);
        cout << "Withdrawl completed successfully\n";
    }
    else {
        cout << "\nThe withdrawl Operation was cancelled ";

    }



}
void WithDrawl() {
    PrintLines(50);
    PrintMiddle("Withdraw window ", 50);
    PrintLines(50);
    cout << "\n";

    string ClientAccountNumber = ReadString("Enter the client account number : ");
    bool found = CheckIfClientExistByAccountNumber(ClientAccountNumber);
    if (found) {
        PrintClientData(ReturnTheClient(ClientAccountNumber));

        ProccedToWithDrawl(ClientAccountNumber);



    }
    else {
        cout << "CLient with (" << ClientAccountNumber << ") account number was not found : \n";
    }


}
///////////////withdraw




////////////////////// total balances
float GetTotalBalances() {
    vector<stClientInfo>Allinfo = ExtractClientsDataFromFile();
    
    float TotalBalances = 0;
    for (const auto& client : Allinfo) {
        TotalBalances += client.AccountBalance;
    }
    return TotalBalances;
}
void PrintTotalBalnces() {
    vector <stClientInfo>AllInfo = ExtractClientsDataFromFile();
    if (AllInfo.size() == 0) {
        cout << "\aThere are currently no clients to display there balances.\n";
    }
    else
    {
        PrintAllClientData(AllInfo);

        float TotalBalances = GetTotalBalances();
        PrintMiddle("Total Balances = " + to_string(TotalBalances), 70);
    }

}
////////////////////// total balances

//////////////////// Transmission

stClientInfo GetSourceClient(string ClientAccountNumber) {
    stClientInfo Client;
    bool found = CheckIfClientExistByAccountNumber(ClientAccountNumber);
    if (found) {
        Client = ReturnTheClient(ClientAccountNumber);
        return Client;
    }
    else {
        cout << "CLient with (" << ClientAccountNumber << ") account number was not found : \n";
    }
   
}
stClientInfo GetDestinationClient(string AccountNumber) {
    stClientInfo Client;
    bool found = CheckIfClientExistByAccountNumber(AccountNumber);
    if (found) {
      Client=  ReturnTheClient(AccountNumber);
      return Client;
    }
    else {
        cout << "CLient with (" << AccountNumber << ") account number was not found : \n";
    }
}
void DoTheTransformation(stClientInfo& SourceClient, stClientInfo& DestinationClient, float Amount=0) {
    Amount = ReadPositiveNumber("Enter the transaction amonut : ");
    cout << "The Desination Account Name is " << DestinationClient.Name << "\n";
    cout << "Are you sure you want to do the transaction (y,n) :";
    char condition = ' ';
    cin >> condition;
    if(condition=='y'||condition=='Y')
    {
        WithDrawlTheMoney(SourceClient.AccountNumber, Amount);
        DepositTheMoney(DestinationClient.AccountNumber, Amount);
    }
    else {
        cout << "\nThe Transaction Operation canceled.\n";
    }
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

        if (NumberOfTries > 0) {
            cout << "\nYou have " << NumberOfTries << " more tries\n";
        }
        else {
            cout << "\nNo more tries left. Access denied!\n";
        }

    } while (NumberOfTries > 0);


}
void Transformations() {
    PrintLines(60);
    PrintMiddle("Transaction window  ", 60);
    PrintLines(60);
    stClientInfo SourceClient;
    stClientInfo DestinationClient;
    string SourceAccountNumber = ReadString("Enter the source client account number : ");
    bool FoundSource = CheckIfClientExistByAccountNumber(SourceAccountNumber);
    if (FoundSource) {
      SourceClient=ReturnTheClient(SourceAccountNumber);
    }
    else {
        cout << "CLient with (" << SourceAccountNumber << ") account number was not found : \n";
        return;
    }
    string DestinationAccountNumber = ReadString("Enter the Destination client account number : ");
    bool foundDestination = CheckIfClientExistByAccountNumber(DestinationAccountNumber);
    if (foundDestination) {
      DestinationClient=ReturnTheClient(DestinationAccountNumber);
    }
    else {
        cout << "CLient with (" << DestinationAccountNumber << ") account number was not found : \n";
        return;
    }
    ValidTransformationsInfo(SourceClient, DestinationClient);
 }

/////////////////// Tansactions
enum enTransactions { enDeposit = 1, enWithDrawl = 2, enTotalBalances = 3, enTransmission, enMainMenu = 5 };
enTransactions ReadTransactionType() {
    short Transaction = 0;
    
    Transaction = ReadNumberInRange("What process do you want to procced : ", 1, 5);
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
        case enTransactions::enDeposit:
            Deposit(); break;
        case enTransactions::enWithDrawl:
            WithDrawl(); break;

        case enTransactions::enTotalBalances:
            PrintTotalBalnces(); break;
        case enTransactions::enTransmission:
       Transformations(); break;

        }
        
        




        if (TransactionType != enTransactions::enMainMenu) {
            system("pause");
        }
    } while (TransactionType != enTransactions::enMainMenu);

}


/////////////////// Tansactions

////////////////////////////////////////////////////////////////////////// Transaction menu



/////////////////////////////////////////////// process
enum enProcess { enAddClient = 1, enDeleteClient = 2, enSearchClient = 3, enUpdateClientInfo = 4, enPrintAllClientsData = 5, enTransaction=6, enExit = 7 };
enProcess ReadProcessType() {
    short Process = 0;
    Process = ReadNumberInRange("What process do you want to procced ", 1, 7);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return static_cast<enProcess>(Process);






}/////////////////////////////// 
/////////////////////////////////////////////// process
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
    cout << setw(40) << "[7] : Exit" << endl;

    PrintLines2(40);

}
void StartTheProgram() {
    enProcess ProcessType;

   do
   {
       system("cls");
       TheStartHeader();
       ProcessType = ReadProcessType();
       
       system("cls");
       switch (ProcessType) {

       case enProcess::enAddClient:
           AddClients(); break;
       case enProcess::enDeleteClient:
           DeleteClientInfo(); break;
       case enProcess::enUpdateClientInfo:
           UpdateClientInfo(); break;
       case enProcess::enPrintAllClientsData:
           PrintAllClientData(ExtractClientsDataFromFile()); break;
       case enProcess::enSearchClient:
           SearchForClientByAccountNumber(); break;
       case enProcess::enTransaction:
           StartTransaction(); break;



       }
     
       if (ProcessType != enProcess::enExit && ProcessType != enProcess::enTransaction) {
           system("pause"); 
       }
   } while (ProcessType != enProcess::enExit);

   EndScreen();

       

    }
///////////////////////////////




  







int main()
{
    StartTheProgram();
}

