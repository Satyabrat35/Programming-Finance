//
// Created by Satyabrat Bhol on 10/12/23.
//

#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include "Helper_SatyabratBhol.h"
using namespace std;

/*
Design Pattern - Template Method is a behavioral design pattern that allows you to defines a skeleton of an algorithm 
in a base class and let subclasses override the steps without changing the overall algorithm’s structure.
*/
class Account {
public:
    Account();

    // set the balance
    void setBalance(string bal);
    // get the balance
    double getBalance() const;
    // print transaciton history
    virtual void displayHistory() const = 0; 

    void fileStatusTemplate();
    // sharedFiles() is implemented in base class to check the cash_balance.txt, which will be used both by StockAccount and BankAccount
    void sharedFiles();
    // privateFiles() is a virtual function, it will be implemented seperately in StockAccount and BankAccount to check these two accounts' own files
    virtual void privateFiles();


    // Helper Function Object
    Helper helpfunc;
};

#endif //PROJECT_ACCOUNT_H
