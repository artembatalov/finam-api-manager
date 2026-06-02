#pragma once
#include <string>
#include <vector>

#include "auth.h"
#include "executor.h"
#include "models.h"

class DataService {
   public:
    DataService(AuthService& auth, Executor& executor);

    std::vector<Bar> Bars(const std::string& symbol, TimeFrame timeframe, Time start, Time end);
    Quote LastQuote(const std::string& symbol);
    OrderBook GetOrderBook(const std::string& symbol);
    std::vector<LatestTrade> LatestTrades(const std::string& symbol);

   private:
    AuthService& auth_;
    Executor& executor_;
};
