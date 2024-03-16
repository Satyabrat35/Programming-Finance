//
// Created by Satyabrat Bhol on 10/12/23.
//

#include "BankAccount_SatyabratBhol.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Helper_SatyabratBhol.h"

using namespace std;

BankAccount::BankAccount()
{
    fileStatusTemplate();
}

void BankAccount::displayDetails() const
{
    cout << "You have $" << fixed << setprecision(2) << getBalance() << " in your bank account." << endl;
}

void BankAccount::displayHistory() const
{
    helpfunc.printAllLines(BANK_HISTORY_FILE); //print all the content of BANK_HISTORY_FILE
}

void BankAccount::logTransaction(int mode, double amount)
{
    string record = "";
    string type = "";
    switch (mode) {
        case 1:
            type = "Deposit";
            break;
        case 2:
            type = "Withdraw";
            break;
        case 3:
            type = "SellStock";
            break;
        case 4:
            type = "BuyStock";
            break;
        default:
            break;
    }
    stringstream ss; //store the type, amount, date and balance to a stringstream
    ss << left << "\n" << setw(16) << type << setw(16) << "$" + helpfunc.convertToStringDecimal(amount) << setw(16) <<
       helpfunc.getCurrentDate() << setw(16) << "$" + helpfunc.convertToStringDecimal(getBalance());
    record = ss.str(); //convert the stringstream to a string
    helpfunc.appendStringToLastLine(BANK_HISTORY_FILE, record); //write to BANK_HISTORY_FILE
}

void BankAccount::depositMoney(double mon)
{
    if (mon <= 0) { // money > 0
        cout << "Error: invalid money." << endl;
        return;
    }
    else {
        stringstream ss;
        ss << fixed << setprecision(2) << getBalance() + mon*1.0;
        setBalance(ss.str()); // set balance
        logTransaction(1, mon); // add the history to file
        cout << "You have successfully deposit $" << fixed << setprecision(2) << mon << "." << endl;
        displayDetails(); // print the details of bank account
    }
}

void BankAccount::withdrawMoney(double mon)
{
    double bal = getBalance();
    if (bal - mon < 0) { // the account must have suficient balance
        cout << "Error: insuficient fund." << endl;
    }
    else {
        stringstream ss;
        ss << fixed << setprecision(2) << bal - mon*1.0;
        setBalance(ss.str()); // set balance
        logTransaction(2, mon); // add history to file
        cout << "You have successfully withdraw $" << fixed << setprecision(2) << mon << "." << endl;
        displayDetails(); // print the details of bank account
    }
}

void BankAccount::privateFiles()
{
    // if BANK_HISTORY_FILE not exist
    if (!helpfunc.doesFileExist(BANK_HISTORY_FILE)) { 
        stringstream ss;
        ss << left << setw(16) << "Event" << setw(16) << "Amount" << setw(16) << "Date" << setw(16) << "Balance";
        string title = ss.str();
        helpfunc.appendStringToLastLine(BANK_HISTORY_FILE, title);
    }
}