#pragma once
#include <string>
#include <vector>

#include "executor.h"
#include "models.h"

class AuthService {
   public:
    AuthService(const std::string& key, Executor& executor);
    AuthService(Executor& executor);
    std::string GetToken();
    std::vector<int64_t> GetAccountIds();

   private:
    void Init();
    void Auth();
    void TokenDetails();
    bool InvalidToken();

    Executor& executor_;
    std::string token_;
    std::string key_;
    TokenInfo info_;
    bool initialized_ = false;
    bool disabled_ = false;
};