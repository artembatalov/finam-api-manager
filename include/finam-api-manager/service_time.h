#pragma once
#include <string>
#include "service_auth.h"

class TimeService {
public:
    TimeService(AuthService& auth, IExecutor& executor);
    std::string ServerTime(const std::string& account_id);
    std::string MachineTime() const;
private:
    AuthService& auth_;
    IExecutor& executor_;
};