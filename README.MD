## Stock and Bank Account Management System
This C++ program implements a stock and bank account management system using an inheritance structure with an abstract base class Account and two derived classes StockAccount and BankAccount. The stock portfolio and bank account are interconnected through the cash balance.

## Path file
If the file path for Matlab is different in your system, please replace those values with the appropriate file path in Makefile
```
MATLAB_INCLUDE = -I/Applications/MATLAB_R2023b.app/extern/include/
MATLAB_LIB = -L/Applications/MATLAB_R2023b.app/bin/maca64 -leng -lmx -lm
RPATH = -Wl,-rpath,/Applications/MATLAB_R2023b.app/bin/maca64
```

## Steps to run
```
make 
./accmgm
```
### Remove executable files
```
make clean
```
Sample Portfolio graph (obtained from code) in the directory by the name - ```Portfolio_Graph.png```

## Warnings
After running the plot graph, I am getting this warning. Please ignore this -
```
Option: CodeCache is full. Compiler has been disabled.
Try increasing the code cache size using -XX:ReservedCodeCacheSize=
```
This is related to Matlab Mac (Apple chip) application, apparently there is no fix for it.


## Files
1. Result_1.txt / Result_2.txt - Stock values with symbol
2. bank_transaction_history.txt - Shows all events (Buy, Sell, Withdraw, Deposit) by the amount and the corresponding account balance
3. cash_balance.txt - Shows current bank account balance
4. stock_details.txt - Shows Company and the current stocks purchased
5. stock_portfolio - Shows change in portfolio value with time and operations
6. stock_transaction_history - Each line in the file corresponds to a specific financial transaction, and the columns provide information about that transaction.

## Account Hierarchy
The program defines an abstract base class Account with two derived classes: StockAccount and BankAccount.

## Stock Portfolio
The StockAccount class manages a stock portfolio using a doubly linked list.
The portfolio is sorted at all times in decreasing order of the total value of each stock (number of shares * price per share).
Stock prices are randomly chosen from two Results.txt files.
Portfolio information is stored in text files to persist data between program runs.
Supports buying and selling shares with transaction history and bank account updates.

## Bank Account
The BankAccount class manages a bank account with an initial balance of $10,000.
Bank account information is stored in a text file for persistence.
Supports depositing and withdrawing money with transaction history.