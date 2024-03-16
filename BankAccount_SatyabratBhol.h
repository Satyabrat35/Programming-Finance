//
// Created by Satyabrat Bhol on 10/12/23.
//

#ifndef PROJECT_BANKACCOUNT_H
#define PROJECT_BANKACCOUNT_H
#include "Account_SatyabratBhol.h"

class BankAccount : public Account {
public:
    BankAccount();

    void displayDetails() const;
    void displayHistory() const;
    // adding history to the file
    void logTransaction(int mode, double amount); 
    // deposit money
    void depositMoney(double mon);
    // withdraw money
    void withdrawMoney(double mon); 

protected:
    virtual void privateFiles(); //check its own files

};

#endif //PROJECT_BANKACCOUNT_H
