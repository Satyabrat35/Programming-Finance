//
// Created by Satyabrat Bhol on 14/12/23.
//

#include "BubbleSort_SatyabratBhol.h"

void BubbleSort::sortAccount(StockAccount& saAcc) {
    
	// cout << "Using Bubble Sort" << endl;
	Node* tempPtr = saAcc.doublyList.head->next;

    // Price of every stock
	while (tempPtr != saAcc.doublyList.tail) {
		tempPtr->price = saAcc.findStockPriceByName(tempPtr->getStockName());
		tempPtr = tempPtr->next;
	}
    
    int sz = saAcc.doublyList.nodeNum;
	for (int i = 1; i <= sz; i++) {
		for (int j = i; j <= sz; j++) {
			Node* stock_1 = saAcc.doublyList.findNodeByPosition(i);
			Node* stock_2 = saAcc.doublyList.findNodeByPosition(j);

			// Check if the nodes are not null
			if (stock_1 && stock_2) { 
                double stock1 = stock_1->getStockNum() * stock_1->price;
                double stock2 = stock_2->getStockNum() * stock_2->price;

                if (stock1 < stock2) {
                    saAcc.doublyList.swapNode(i, j);
                }
            }
		}
	}
}