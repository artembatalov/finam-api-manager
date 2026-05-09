#pragma once
#include <string>
#include <string>
#include "auth.h"

class TimeService {
public:
    TimeService(AuthService& auth, Executor& executor);
    std::string ServerTime(const std::string& account_id);
    std::string MachineTime() const;
private:
    AuthService& auth_;
    Executor& executor_;
};