//
// Created by Satyabrat Bhol on 14/12/23.
//

#include "SelectionSort_SatyabratBhol.h"

void SelectionSort::sortAccount(StockAccount& saAcc) {
    // Implement Selection Sort algorithm here
    // cout << "Using Selection Sort" << endl;

	Node* tempPtr = saAcc.doublyList.head->next;

    // Price of every stock
	while (tempPtr != saAcc.doublyList.tail) {
		tempPtr->price = saAcc.findStockPriceByName(tempPtr->getStockName()); 
		tempPtr = tempPtr->next;
	}
    int sz = saAcc.doublyList.nodeNum;
	for (int i = 1; i <= sz - 1; i++) {
		int minm = i;
		for (int j = i+1 ; j <= sz; j++) {
			Node* stock_1 = saAcc.doublyList.findNodeByPosition(minm);
			Node* stock_2 = saAcc.doublyList.findNodeByPosition(j);

			double stock1 = (stock_1->getStockNum() * stock_1->price);
			double stock2 = (stock_2->getStockNum() * stock_2->price);

			if (stock1 < stock2) {
				minm = j;
			}
		}
		saAcc.doublyList.swapNode(i, minm);
	}
}