#pragma once
#include "models.h"
#include "auth.h"
#include "executor.h"

class DataService {
public:
    DataService(AuthService& auth, Executor& executor);

    void Bars();
    void OrderBook();
    void LastQuote();
    void LatestTrades();
private:
    AuthService& auth_;
    Executor& executor_;
};