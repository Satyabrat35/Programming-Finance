//
// Created by Satyabrat Bhol on 10/12/23.
//

#include "Account_SatyabratBhol.h"


void Account::setBalance(string bal)
{
    helpfunc.writeStringToFile(CASH_BALANCE_FILE, bal); // write balance to file
}

Account::Account()
{
    fileStatusTemplate(); // check file status first
}

double Account::getBalance() const
{
    string newest = helpfunc.getLastLineOfFile(CASH_BALANCE_FILE); // get the last line from the file
    double balance_from_file = atof(newest.c_str()) * 1.0;
    return balance_from_file;
}

void Account::fileStatusTemplate()
{
    sharedFiles(); // check shared file
    privateFiles(); // check private file
}

void Account::sharedFiles()
{
    // If CASH_BALANCE_FILE not exist, initialize it to "10000"
    if (!helpfunc.doesFileExist(CASH_BALANCE_FILE)) { 
        string m = "10000.00";
        helpfunc.appendStringToLastLine(CASH_BALANCE_FILE, m);
    }
}

// interface
void Account::privateFiles()
{ }