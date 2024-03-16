//
// Created by Satyabrat Bhol on 14/12/23.
//

#ifndef PROJECT_BUBBLESORT_H
#define PROJECT_BUBBLESORT_H

#include "SortStratergy_SatyabratBhol.h"
#include "StockAccount_SatyabratBhol.h"

class BubbleSort : public SortStratergy {
public:
    void sortAccount(StockAccount& saAcc) override;
};

#endif //PROJECT_BUBBLESORT_H
