//
// Created by Satyabrat Bhol on 10/12/23.
//
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "StockAccount_SatyabratBhol.h"
#include "Helper_SatyabratBhol.h"
#include "BubbleSort_SatyabratBhol.h"
#include "SelectionSort_SatyabratBhol.h"

using namespace std;

StockAccount::StockAccount()
{
    fileStatusTemplate();
    sort_stratergy = new SelectionSort();
    con_pattern = new Context(sort_stratergy);

    retrieveAllStock(); 
    // Random seed
    srand((unsigned)time(0));
}

StockAccount::~StockAccount()
{
    delete con_pattern;
    con_pattern = NULL;
    updatePortfolioValue();
}

double StockAccount::getPortfolioFromFile() const
{
    string newest = helpfunc.getLastLineOfFile(PORTFOLIO_FILE); //get the last portfolio value
    string tok = helpfunc.getNthWordInString(newest, 1);
    double p = atof(tok.c_str()) * 1.0;
    return p;
}

void StockAccount::setPortfolio(double p)
{
    portfolio = p;
    updatePortfolioValue(); //store portfolio to file
}

double StockAccount::getPortfolio()
{
    return portfolio;
}

void StockAccount::displayDetails()
{
    cout << "Cash balance = $" << getBalance() << endl;
    cout << left;
    cout << setw(16) << "CompSymbol" << setw(12) << "Number" << setw(16) << "PricePerShare" << setw(16) << "TotalValue" << endl;

    Node* currentPtr = doublyList.getHead()->getNext(); 
    double myBalance = 0.0;

    while (currentPtr != doublyList.getTail()) { 
        myBalance += currentPtr->getPrice() * currentPtr->getStockNum();
        //print the details of stocks
        cout << setw(16) << currentPtr->getStockName() << setw(12) << currentPtr->getStockNum() << setw(16) <<
             "$" + helpfunc.convertToStringDecimal(currentPtr->getPrice()) << setw(16) <<
             "$" + helpfunc.convertToStringDecimal(currentPtr->getPrice()*currentPtr->getStockNum()) << endl;
        currentPtr = currentPtr->getNext();
    }
    // Determine if the user has stocks
    if (doublyList.getSize() == 0) { 
        cout << "You do not have any stock yet." << endl;
    }
    cout << "Total portfolio value: $" << myBalance + getBalance() << endl;
    setPortfolio(myBalance + getBalance());
}

void StockAccount::displayHistory() const
{
    helpfunc.printAllLines(STOCK_HISTORY_FILE); // print all the content of STOCK_HISTORY_FILE
}

void StockAccount::applySorting(string type) {
    if (sort_stratergy) {
        delete sort_stratergy;
        sort_stratergy = NULL;
    }

    if (type == "SelectionSort") {
        sort_stratergy = new SelectionSort();
    } else {
        sort_stratergy = new BubbleSort();
    }

    if (sort_stratergy) {
        sort_stratergy->sortAccount(*this);
    }
}

void StockAccount::setSortStratergy(SortStratergy* stratergy) {
    if (stratergy) {
        delete sort_stratergy;  // Delete the current strategy if it exists
        sort_stratergy = stratergy;
    }
}

double StockAccount::findStockPriceByName(string name) const
{
    double random = rand() / double(RAND_MAX);
    string result_s;
    double price;
    // Randomize the file selection
    if (random >= 0.5) {
        result_s = helpfunc.searchFileForKey(RESULT_1, name);
    } else {
        result_s = helpfunc.searchFileForKey(RESULT_2, name);
    }
    // No stock found
    if (result_s == "") {
        price = -1; 
    } else {
        price = atof(helpfunc.getNthWordInString(result_s, 2).c_str()); 
    }

    return price * 1.0;
}



void StockAccount::showStockInformation(string name)
{

    double price = findStockPriceByName(name); 
    if (price > 0) { // stock found
        cout << left;
        cout << setw(16) << "Company Symbol" << setw(16) << "Price per share" << endl;
        string price_s = "$" + helpfunc.convertToStringDecimal(price);
        cout << setw(16) << name << setw(16) << price_s << endl;
    } else {
        cout << "Error: Stock not found. Cannot display the price." << endl;
    }
}

void StockAccount::retrieveAllStock()
{
    ifstream ifs;
    ifs.open(STOCK_DETAILS_FILE);
    if (ifs.fail()) {
        cerr << "Error: " << strerror(errno) << endl;
    } else {
        string line;
        int num = 0;
        while (getline(ifs, line)) {
            if (num++ == 0) continue; 
            string name = helpfunc.getNthWordInString(line, 1); // get the name
            int num = atoi(helpfunc.getNthWordInString(line, 3).c_str()); // get the num
            Node* node = new Node(name, num); // new node
            doublyList.insertNode(node); // insert it to the doublyList
        }
        ifs.close();
    }
}

void StockAccount::sellStocks(string name, int num, double price, BankAccount &baAcc)
{
    Node* stock = doublyList.findNode(name); //find the stock

    if (stock == nullptr) {
        cout << "Transaction failed: You do not own this stock." << endl;
    } else {
        double priceNow = findStockPriceByName(name); 
        if (priceNow > 0) {
            if (num > stock->getStockNum()) { // number user wants to sell is greater than what he owns
                cout << "Transaction failed: Insufficient stock shares" << endl;
                return;
            } else {
                if (priceNow < price) { // price per stock lower than what user wants to sell for
                    cout << "Transaction failed: Price per stock is lower than what you want to sell for" << endl;
                    return;
                } else {
                    if (stock->getStockNum() - num == 0) {
                        doublyList.deleteNode(name); // if user has 0 share of the stock, delete it from doublyList
                    } else {
                        stock->setStockNum(stock->getStockNum() - num); // or subtract the number
                    }

                    stringstream ss;
                    ss << fixed << setprecision(2) << getBalance() + num*priceNow*1.0;
                    setBalance(ss.str()); // set cash balance
                    baAcc.logTransaction(3, num*priceNow); // add the history of bank account
                    logTransaction(1, name, num, priceNow); // add the history of stock account
                    updateStockFile(); // store the newest doublyList to file
                    cout << "You have selled " << num << " shares of " << name << " at $" << fixed << setprecision(2) << priceNow << " for a total of $" << priceNow*num << "." << endl;
                }
            }
        }
        else {
            cout << "Error: Stock not found." << endl;
        }
    }
}

void StockAccount::purchaseStocks(string name, int num, double price, BankAccount& baAcc)
{

    double priceNow = findStockPriceByName(name); // find the price

    if (priceNow > 0) {
        if (price < priceNow) { 
            cout << "Transaction failed: Your price is too low." << endl;
            return;
        }
        else {
            double totalCost = num*priceNow*1.0; // calculate the total cost
            double bal = getBalance(); // get the cash balance
            if (totalCost > bal) { // insufficient cash balance
                cout << "Transaction failed: Insufficient cash balance." << endl;
            }
            else {
                Node* stock = doublyList.findNode(name); // find if the stock has owned
                // stock not owned, build a new node and insert it
                if (stock == nullptr) {
                    stock = new Node(name, num);
                    doublyList.insertNode(stock);
                } else {
                    // add the share of the stock
                    stock->setStockNum(stock->getStockNum() + num); 
                }

                stringstream ss;
                ss << fixed << setprecision(2) << bal - totalCost;
                setBalance(ss.str()); // set cash balance
                baAcc.logTransaction(4, totalCost); // add the history of bank account
                logTransaction(2, name, num, priceNow); // add the history of stock account
                updateStockFile(); // store the newest doublyList to file
                cout << "You have pruchased " << num << " shares of " << name << " at $" << fixed << setprecision(2) << priceNow << " for a total of $" << priceNow*num << "." << endl;
            }
        }
    } else {
        cout << "Error: Stock not found." << endl;
    }
}

void StockAccount::updateStockFile()
{
    // rewrite all the names and shares of stocks to the file
    helpfunc.clearFile(STOCK_DETAILS_FILE);
    string title = "CompSymbol\tNumber\t";
    helpfunc.appendStringToLastLine(STOCK_DETAILS_FILE, title);

    Node* currentPtr = doublyList.getHead()->getNext();

    while (currentPtr != doublyList.getTail()) {
        string stock = "\n" + currentPtr->getStockName() + "\t\t" + helpfunc.convertToString(currentPtr->getStockNum());
        helpfunc.appendStringToLastLine(STOCK_DETAILS_FILE, stock);
        currentPtr = currentPtr->getNext();
    }
}

void StockAccount::updatePortfolioValue()
{
    // Add a new record of portfolio
    string balance_record = "\n" + helpfunc.convertToStringDecimal(getPortfolio()) + "\t" + helpfunc.convertTimeToString(helpfunc.getCurrentTimeInSeconds());
    helpfunc.appendStringToLastLine(PORTFOLIO_FILE, balance_record);
}

void StockAccount::privateFiles()
{
    // If PORTFOLIO_FILE, STOCK_HISTORY_FILE or STOCK_DETAILS_FILE does not exist, build it and initialize it.
    if (!helpfunc.doesFileExist(PORTFOLIO_FILE)) {
        string balance_record = "10000.00\t" + helpfunc.convertTimeToString(helpfunc.getCurrentTimeInSeconds());
        helpfunc.appendStringToLastLine(PORTFOLIO_FILE, balance_record);
    } else {
        setPortfolio(getPortfolioFromFile());
    }

    if (!helpfunc.doesFileExist(STOCK_HISTORY_FILE)) {
        stringstream ss;
        ss << left << setw(16) << "Event" << setw(16) << "CompSymbol" << setw(12) << "Number" << setw(16) << "PricePerShare" << setw(16) << "TotalValue" << setw(16) << "Time";
        string title = ss.str();
        helpfunc.appendStringToLastLine(STOCK_HISTORY_FILE, title);
    }

    if (!helpfunc.doesFileExist(STOCK_DETAILS_FILE)) {
        string title = "CompSymbol\tNumber\t";
        helpfunc.appendStringToLastLine(STOCK_DETAILS_FILE, title);
    }
}

void StockAccount::logTransaction(int mode, string name, int num, double pricepershare)
{
    string record = "";
    string type = "";
    switch (mode) {
        case 1:
            type = "Sell";
            break;
        case 2:
            type = "Buy";
            break;
        default:
            break;
    }

    stringstream ss; //store the type, name, number of share, price per share and time to a stringstream
    ss << left << "\n" << setw(16) << type << setw(16) << name << setw(12) << helpfunc.convertToString(num) <<
       setw(16) << "$" + helpfunc.convertToStringDecimal(pricepershare) << setw(16) << "$" + helpfunc.convertToStringDecimal(num*pricepershare) <<
       setw(16) << helpfunc.getCurrentTime();
    record = ss.str(); //convert it to string and add it to the last of STOCK_HISTORY_FILE
    helpfunc.appendStringToLastLine(STOCK_HISTORY_FILE, record);
}

