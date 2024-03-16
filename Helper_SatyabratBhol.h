//
// Created by Satyabrat Bhol on 11/12/23.
//

#ifndef PROJECT_HELPER_H
#define PROJECT_HELPER_H
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// define the macros for the files
#define RESULT_1 "data/Result_1.txt"
#define RESULT_2 "data/Result_2.txt"

#define BANK_HISTORY_FILE "data/bank_transaction_history.txt"
#define CASH_BALANCE_FILE "data/cash_balance.txt"
#define PORTFOLIO_FILE "data/stock_portfolio.txt"
#define STOCK_DETAILS_FILE "data/stock_details.txt"
#define STOCK_HISTORY_FILE "data/stock_transaction_history.txt"

class Helper {
public:
    Helper();
    // Date as mm/dd/yyyy now
    string getCurrentDate() const; 
    // Time as hh:mm:ss now
    string getCurrentTime() const; 
    // Time in sec
    time_t getCurrentTimeInSeconds() const; 
    // Check the file exists or not
    bool doesFileExist(string file_name) const; 
    // Clear the file
    void clearFile(string file_name); 
    // Search the file for key
    string searchFileForKey(string file_name, string key) const; 
    // Write balance to file
    void writeStringToFile(string file_name, string s);  
    // Add a string to the last of a file
    void appendStringToLastLine(string file_name, string str); 
    // Get the last line of a file
    string getLastLineOfFile(string file_name) const; 
    // Get the n-th word in file
    string getNthWordInString(string str, int num) const; 
    // Get the line numbers of a file
    int getNumberOfLines(string file_name) const;
    // Print all the content of the file
    void printAllLines(string file_name) const; 
    // Convert a double to string (2 decimal precision)
    string convertToStringDecimal(double d) const; 
    // Convert a double to string
    string convertToString(double d) const;  
    // Convert a long to string
    string convertTimeToString(long d) const;  
};

#endif //PROJECT_HELPER_H
