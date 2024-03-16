//
// Created by Satyabrat Bhol on 14/12/23.
//
#include "SortStratergy_SatyabratBhol.h"

Context::Context(SortStratergy* sortstat) {
	this->sortstat = sortstat;
}

void Context::sortUsingContext(StockAccount &saAcc) {
    this->sortstat->sortAccount(saAcc);
}

Context::~Context() {
    delete this->sortstat;
}