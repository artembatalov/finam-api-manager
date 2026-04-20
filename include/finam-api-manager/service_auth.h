#pragma once
#include <string>
#include <vector>
#include "models.h"
#include "executor.h"

class AuthService {
public:
    AuthService(const std::string& key, IExecutor& executor);
    std::string GetToken();
    std::vector<int64_t> GetAccountIds() const;

private:
    void Auth();
    void TokenDetails();
    bool InvalidToken();

    IExecutor& executor_;
    std::string token_;
    std::string key_;
    TokenInfo info_;
};