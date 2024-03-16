//
// Created by Satyabrat Bhol on 14/12/23.
//

#ifndef PROJECT_SORTSTRATERGY_H
#define PROJECT_SORTSTRATERGY_H


/* 
Design Pattern - Stratergy Pattern
Strategy is a behavioral design pattern that turns a set of behaviors 
into objects and makes them interchangeable inside original context object. 
*/ 

class StockAccount;
class SortStratergy {
public:
    virtual void sortAccount(StockAccount& saAcc) = 0;
    virtual ~SortStratergy() = default;
};

class Context {
public:
    Context(SortStratergy* sortstat);
    void sortUsingContext(StockAccount &saAcc);
    ~Context();

private:
    SortStratergy* sortstat;
};

#endif //PROJECT_SORTSTRATERGY_H
