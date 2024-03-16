//
// Created by Satyabrat Bhol on 10/12/23.
//

#ifndef PROJECT_STOCKACCOUNT_H
#define PROJECT_STOCKACCOUNT_H
#include <iostream>
#include "Account_SatyabratBhol.h"
#include "BankAccount_SatyabratBhol.h"
#include "SortStratergy_SatyabratBhol.h"
#include "DoublyLinkedList_SatyabratBhol.h"

using namespace std;

class SortStratergy;
class Context;
class StockAccount : public Account {

    friend class BubbleSort;
    friend class SelectionSort;

public:
    StockAccount();
    ~StockAccount();

    // Portfilio value from file
    double getPortfolioFromFile() const; 
    // Set portfolio value
    void setPortfolio(double p);  
    double getPortfolio();
    void displayDetails();
    void displayHistory() const;

    void applySorting(string type);  
    void setSortStratergy(SortStratergy* stratergy);

    // get all stock from file and store it to doubly linked list
    void retrieveAllStock(); 
    // sell stocks
    void sellStocks(string name, int num, double price, BankAccount &baAcc); 
    // buy stocks
    void purchaseStocks(string name, int num, double price, BankAccount &baAcc); 
    // find the price of a stock randomly from files by using its name
    double findStockPriceByName(string name) const; 
    // show the detail of a stock
    void showStockInformation(string name); 
    // write the new stock information to file
    void updateStockFile(); 
    // write the new portfolio value along with the time to file
    void updatePortfolioValue(); 
    // add history to file
    void logTransaction(int mode, string name, int num, double pricepershare); 
    // MATLAB graph
    void plotGraphUsingMatlab(); 

    SortStratergy* sort_stratergy;
    Context* con_pattern;

private:
    DoublyLinkedList doublyList;
    double portfolio;

protected:
    virtual void privateFiles(); //check its own files
};

#endif //PROJECT_STOCKACCOUNT_H
