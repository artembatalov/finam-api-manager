#pragma once
#include "auth.h"
#include "executor.h"

class AccountService {
public:
    AccountService(AuthService& auth, Executor& executor);
    void GetAccount();
    void Trades();
    void Transactions();
private:
    AuthService& auth_;
    Executor& executor_;
};