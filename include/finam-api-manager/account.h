#pragma once
#include "auth.h"
#include "executor.h"

class AccountService {
   public:
    AccountService(AuthService& auth, Executor& executor);
    Account GetAccount(int64_t account_id);
    std::vector<Trade> Trades(int64_t account_id, size_t limit, Time start, Time end);
    std::vector<Transaction> Transactions(int64_t account_id, size_t limit, Time start, Time end);

   private:
    AuthService& auth_;
    Executor& executor_;
};