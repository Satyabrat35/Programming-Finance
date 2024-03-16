//
// Created by Satyabrat Bhol on 14/12/23.
//

#ifndef PROJECT_SELECTIONSORT_H
#define PROJECT_SELECTIONSORT_H

#include "SortStratergy_SatyabratBhol.h"
#include "StockAccount_SatyabratBhol.h"

class SelectionSort : public SortStratergy {
public:
    void sortAccount(StockAccount& saAcc) override;
};

#endif //PROJECT_SELECTIONSORT_H
