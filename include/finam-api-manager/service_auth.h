#pragma once
#include <string>
#include "models.h"
#include "executor.h"

class AuthService {
public:
    AuthService(const std::string& key, IExecutor& executor)
        : key_(key), executor_(executor) {}

    std::string GetToken() const {
        // updating mechanism...
        return token_;
    }
private:
    void Auth();
    void TokenDetails();

    IExecutor& executor_;
    std::string token_;
    std::string key_;
    TokenInfo info_;
};