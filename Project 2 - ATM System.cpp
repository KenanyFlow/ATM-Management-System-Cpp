#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include <iostream>
using namespace std;

const string ClientsFileName = "Clients_Data.text";

enum enQuickWithdraw
{ 
    A_20=1, A_50 = 2 , A_100 = 3 , A_200 = 4 , A_400 = 5
   , A_600 = 6 , A_800 = 7 , A_1000 = 8 , Exit=9
};
enum enATM_Menue{Q_Withdraw=1 , N_Withdraw=2 , D_eposit=3 , C_Balance=4 ,Change_Pass=5 ,L_ogout=6};

struct stClientInfo
{
    string Name, Account_Number, Phone, Pin_Code;
    double Account_Balance;
    bool MarkForDelet = false;

};

stClientInfo CurrentUser;

// Files
void CreateFileIfNotExist(const string& FileName) 
{
    fstream file;
    file.open(FileName, ios::app); // Open the file in append mode. If it doesn't exist, it will be created.
    if (file.is_open()) {
        file.close();
    }
    else {
        cerr << "Error: Could not create file " << FileName << endl;
    }
}


vector <string> SplitString(string& S1, string Delim)
{
    vector<string> vString;
    string sword;
    short pos = 0;
    string s1_copy = S1;

    while ((pos = s1_copy.find(Delim)) != string::npos)
    {
        sword = s1_copy.substr(0, pos);
        if (!sword.empty())
        {
            vString.push_back(sword);
        }
        s1_copy.erase(0, pos + Delim.length());
    }
    if (!s1_copy.empty())
    {
        vString.push_back(s1_copy);
    }

    return vString;
}
//                                 Give Information to each Client
stClientInfo ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    vector<string> vClientData = SplitString(Line, Seperator);

    stClientInfo Client;
    Client.Account_Number = vClientData[0];
    Client.Pin_Code = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Account_Balance = stod(vClientData[4]);

    return Client;
}
string ConvertRecordToLine(stClientInfo Client, string Delim = "#//#")
{
    string ClintInfo = "";

    ClintInfo += Client.Account_Number + Delim;
    ClintInfo += Client.Pin_Code + Delim;
    ClintInfo += Client.Name + Delim;
    ClintInfo += Client.Phone + Delim;
    ClintInfo += to_string(Client.Account_Balance);

    return ClintInfo;
}

//                                  Vector Of Stuctures 
vector<stClientInfo> LoadCleintsDataFromFile(string FileName)
{
    vector<stClientInfo> vClientRecords;
    fstream MyFile1;

    MyFile1.open(FileName, ios::in);
    if (MyFile1.is_open())
    {
        string line;
        while (getline(MyFile1, line))
        {
            stClientInfo Client = ConvertLinetoRecord(line);
            vClientRecords.push_back(Client);
        }
    }
    else {
        cerr << "Error: Could not open file " << FileName << endl; //print error  immediately sent to the output destination (usually the console) without waiting. This is in contrast to cout, which is buffered, meaning it may wait before actually displaying the output until the buffer is full or flushed.


    }
    MyFile1.close();
    return vClientRecords;
}

void AddDataLineToFile(string FileName, string DataLine)
{
    fstream My_File;
    My_File.open(FileName, ios::out | ios::app);
    if (My_File.is_open())
    {
        My_File << DataLine << endl;
    }
    else {
        cerr << "Error: Could not open file " << FileName << endl;
    }

    My_File.close();

}

vector <stClientInfo> SaveCleintsDataToFile(string FileName, vector<stClientInfo> vClients)
{
    fstream My_File;
    string DataLine;
    My_File.open(FileName, ios::out);
    if (My_File.is_open())
    {
        for (stClientInfo& C : vClients)
        {
            if (!(C.MarkForDelet))
            {
                DataLine = ConvertRecordToLine(C);
                AddDataLineToFile(FileName, DataLine);
            }
        }
        My_File.close();
    }
    return vClients;
}

 // Read Login Info
string ReadClientAccountNumber()
{
    string AccNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccNumber;
    cout << endl;
    return AccNumber;
}
string ReadClientPinCode()
{
    string PinCode = "";
    cout << "\nPlease enter PinCode? ";
    cin >> PinCode;
    cout << endl;
    return PinCode;
}

bool FindUserByAccountNumberAndPinCode(const string& AccNumber, const string& PinCode, stClientInfo& User)
{
    vector<stClientInfo> vUsers;
    vUsers = LoadCleintsDataFromFile(ClientsFileName);
    for (stClientInfo& U : vUsers)
    {
        if (U.Account_Number == AccNumber && U.Pin_Code == PinCode)
        {
            User = U;
            return true;
        }
    }
    return false;
}


void PrintBalance(stClientInfo Client)
{
    cout << "Your Balance is: "<<Client.Account_Balance;
}
// Quick Withdraw
enQuickWithdraw AskFor_QuickWithdrawAmount_Mood()
{
    int MoodNum;

    do
    {
        cout << "\nChoose What do you want to do -> [1 to 9]? ";
        cin >> MoodNum;

    } while (MoodNum < 1 || MoodNum>9);
    return (enQuickWithdraw)MoodNum;
}
void QuickWithDrawMood(enQuickWithdraw withdraw, int &WithdrawAmount)
{
    switch (withdraw)
    {
    case A_20:
        WithdrawAmount= 20;
        break;

    case A_50:
        WithdrawAmount= 50;
        break;
  
    case A_100:
        WithdrawAmount= 100;
        break;
  
    case A_200:
        WithdrawAmount= 200;
        break;
   
    case A_400:
        WithdrawAmount= 400;
        break;

    case A_600:
        WithdrawAmount= 600;
        break;
    
    case A_800:
        WithdrawAmount= 800;
        break;

    case A_1000:
        WithdrawAmount= 1000;
        break;
    case Exit:
        WithdrawAmount = -1;
        break;
    }
}
void QuickWithDrawTransaction(vector<stClientInfo>& vClients,stClientInfo& Client)
{
    int WithDraw_Amount;
    char ensure;
    bool Invalid = false;

            for (stClientInfo& C : vClients)
            {
                if (C.Account_Number == CurrentUser.Account_Number)
                { 
                    while (!Invalid)
                    {
                        QuickWithDrawMood(AskFor_QuickWithdrawAmount_Mood(), WithDraw_Amount);
                        if (WithDraw_Amount == -1)
                            return;

                        // Check if the withdrawal amount is less than or equal to the account balance
                        if (WithDraw_Amount <= C.Account_Balance)
                        {
                            C.Account_Balance -= WithDraw_Amount;
                            Client.Account_Balance = C.Account_Balance;

                            Invalid = true;
                            cout << "\n\nAre you sure you want to perform this transaction (Y or N)? ";
                            cin >> ensure;

                            if (ensure == 'y' || ensure == 'Y')
                            {
                                SaveCleintsDataToFile(ClientsFileName, vClients);
                                cout << "\n\nDone Successfully. New balance is: " << C.Account_Balance;
                            }
                            else
                            {
                                cout << "Transaction cancelled.\n";
                            }
                        }
                        else
                        {
                            Invalid = false;

                            cout << "\nAmount exceeds the balance, you can withdraw up to: " << C.Account_Balance << endl;
                            cout << "Please enter a valid amount.\n";
                        }

                    }
                    
                }
            }

    
}
void QuickWithDrawScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tWithdraw Screen\n";
    cout << "====================================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
    PrintBalance(CurrentUser);
}

void StartQuickWithDrawTransaction()
{
    QuickWithDrawScreen();

    vector<stClientInfo> vClients = LoadCleintsDataFromFile(ClientsFileName);

    QuickWithDrawTransaction( vClients,CurrentUser);
}

// Normal Withdraw
int ReadNormalWithdrawAmount()
{
    int Amount;
    do
    {
        cout << "\nEnter an Amount multiple of 5 `s ? ";
        cin >> Amount;
    } while (Amount % 5 !=0);
    return Amount;
}
bool NormalWithDrawTransaction( vector<stClientInfo>& vClients, stClientInfo& Client)
{
    
    int WithDraw_Amount;
    char ensure;
    bool Invalid = false;

        for (stClientInfo& C : vClients)
        {
            if (C.Account_Number == CurrentUser.Account_Number)
            {
                while (!Invalid)
                {
                    WithDraw_Amount = ReadNormalWithdrawAmount();

                    // Check if the withdrawal amount is less than or equal to the account balance
                    if (WithDraw_Amount <= C.Account_Balance)
                    {
                        C.Account_Balance -= WithDraw_Amount;
                        Client.Account_Balance = C.Account_Balance;


                        cout << "\n\nAre you sure you want to perform this transaction (Y or N)? ";
                        cin >> ensure;

                        if (ensure == 'y' || ensure == 'Y')
                        {
                            SaveCleintsDataToFile(ClientsFileName, vClients);
                            cout << "\n\nDone Successfully. New balance is: " << C.Account_Balance;
                            Invalid = true;
                            return true;
                        }
                        else
                        {
                            cout << "Transaction cancelled.\n";
                            return false;
                        }
                    }
                    else
                    {
                        Invalid = false;

                        cout << "\nAmount exceeds the balance, you can withdraw up to: " << C.Account_Balance << endl;
                        cout << "Please enter a valid amount.\n";
                    }
                }
            }
        }

    
}
void NormalWithDrawScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tWithdraw Screen\n";
    cout << "====================================================\n\n";
    PrintBalance(CurrentUser);
}

void StartNormalWithDrawTransaction()
{
    NormalWithDrawScreen();

    vector<stClientInfo> vClients = LoadCleintsDataFromFile(ClientsFileName);

    NormalWithDrawTransaction(vClients,CurrentUser);
}

// Deposit  
int ReadDepositAmount()
{
    int Amount;
    do
    {
        cout << "\nEnter a Positive Deposit Amount ? ";
        cin >> Amount;
    } while (Amount <= 0);
    return Amount;
}
bool DepositTransaction(vector<stClientInfo>& vClients,stClientInfo& Client)
{
   
    int WithDraw_Amount;
    char ensure;

    WithDraw_Amount = ReadDepositAmount();
    
    
    for (stClientInfo& C : vClients)
    {
        if (C.Account_Number == CurrentUser.Account_Number)
        {
            C.Account_Balance += WithDraw_Amount;
            Client.Account_Balance = C.Account_Balance;

            cout << "\n\nAre you sure you want to perform this transaction (Y or N)? ";
            cin >> ensure;

            if (ensure == 'y' || ensure == 'Y')
            {
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.Account_Balance;
                return true;
            }
            else
            {
                cout << "Transaction cancelled.\n";
                return false;
            }

        }
    }
}
void DepositTrancactionScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tDeposit Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    
    DepositTransaction(vClients,CurrentUser);
}

// Check Balance
void ShowCheckBalanceScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tCheck Balance Screen\n";
    cout << "===========================================\n";
    cout << "Your Balance is " << CurrentUser.Account_Balance << "\n";

}

// Change Password

string ReadOldPassword()
{
    string OldPass;
    cout << "\nPlease enter Your Old Password: ";
        getline(cin >> ws, OldPass);
        return OldPass;
}
string ReadNewPassword()
{
    string ReadNewPassword;
    cout << "\nPlease enter Your New Password: ";
    getline(cin >> ws, ReadNewPassword);
    return ReadNewPassword;
}

bool CheckOldPass(string OldPass)
{
    if (OldPass == CurrentUser.Pin_Code)
    {
        return true;
    }
    return false;
}
bool ChangeOldPassword(vector<stClientInfo>& vClients, stClientInfo& Client)
{
    string OldPass;
    char ensure;
    bool Correct = false;

    for (stClientInfo& C : vClients)
    {
        if (C.Account_Number == CurrentUser.Account_Number)
        {
            while (!Correct)
            {
                OldPass = ReadOldPassword();

                if (CheckOldPass(OldPass))
                {

                    C.Pin_Code = ReadNewPassword();
                    Client.Pin_Code = C.Pin_Code;

                    cout << "\n\nAre you sure you want to perform this Operation (Y or N)? ";
                    cin >> ensure;
                    Correct = true;

                    if (ensure == 'y' || ensure == 'Y')
                    {
                        SaveCleintsDataToFile(ClientsFileName, vClients);
                        cout << "\n\nDone Successfully. New Password is: " << C.Pin_Code;
                        return true;
                    }
                    else
                    {
                        cout << "Operation cancelled.\n";
                        return false;
                    }

                }
                else
                {
                    Correct = false;
                    cout << "\nIncorrect Password,Please try Again.\n";
                }

            }


        }
    }

}
void ChangePassScreen()
{
    system("cls");
    cout << "\n\n====================================================\n";
    cout << "\tChange Password Screen\n";
    cout << "====================================================\n\n";

    vector<stClientInfo> vClients;
    vClients = LoadCleintsDataFromFile(ClientsFileName);

    ChangeOldPassword(vClients, CurrentUser);

}

// Menue Screen

void ShowMainMenue()
{
    system("cls");
   // printf("                 Hellow,%s                          \n", CurrentUser.Name);
    cout << "\t\tHello," << CurrentUser.Name << endl;
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Change Password.\n";
    cout << "\t[6] Logout.\n";
    cout << "===========================================\n";
}

void DoChoosenMood(enATM_Menue);
enATM_Menue AskForMood();
void GoBackToMainMenue()
{
    cout << "\n\nBress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
    DoChoosenMood(AskForMood());
}
enATM_Menue AskForMood()
{
    int MoodNum;

    do
    {
        cout << "\nChoose What do you want to do -> [1 to 6]? ";
        cin >> MoodNum;

    } while (MoodNum < 1 || MoodNum>6);
    return (enATM_Menue)MoodNum;
}
void StartLoginScreen();
void DoChoosenMood(enATM_Menue Mood)
{
    switch (Mood)
    {
    case Q_Withdraw:
        StartQuickWithDrawTransaction();
        GoBackToMainMenue();
        break;
    case N_Withdraw:
        StartNormalWithDrawTransaction();
        GoBackToMainMenue();
        break;
    case D_eposit:
        DepositTrancactionScreen();
        GoBackToMainMenue();
        break;
    case C_Balance:
        ShowCheckBalanceScreen();
        GoBackToMainMenue();
        break;
    case Change_Pass:
        ChangePassScreen();
        GoBackToMainMenue();
    case L_ogout:
        //   Back to login Screen
        StartLoginScreen();
        break;
    }
}
void GoToMainMenueScreen()
{
    system("cls");
    ShowMainMenue();
    DoChoosenMood(AskForMood());
}

// LoginScreen

void ShowLoginScreen()
{
    system("cls");
    cout << "====================================================\n";
    cout << "\t\t Login Screen\n";
    cout << "====================================================\n";
}
string TrimString(string str)
{
    str.erase(0, str.find_first_not_of(' '));  // Trim leading spaces
    str.erase(str.find_last_not_of(' ') + 1);  // Trim trailing spaces
    return str;
}
string AskForAccNumber() {
    string UserName;
    cout << "Enter Account Number? ";
    getline(cin >> ws, UserName);
    return TrimString(UserName);
}
string AskForPinCode()
{
    string Password;
    cout << "Enter Pin Code? ";
    getline(cin >> ws, Password);
    return TrimString(Password);
}

void StartLoginScreen()
{
    bool loginSuccess = false;
    bool InvalidInput = false;
    system("cls");
    while (!loginSuccess)
    {
        ShowLoginScreen();

        if (InvalidInput)
        {
            cout << "\nInvalid (Account Number / Pin Code). Please try again.\n";
            InvalidInput = false;
        }
        string U = AskForAccNumber();
        string P = AskForPinCode();

        if (FindUserByAccountNumberAndPinCode(U, P, CurrentUser))
        {
            loginSuccess = true;
            GoToMainMenueScreen();
        }
        else
        {
            InvalidInput = true;
        }
    }
}

void StartProgram()
{
    CreateFileIfNotExist(ClientsFileName);
    StartLoginScreen();
}

int main()
{
    StartProgram();
}

