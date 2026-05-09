#pragma once
#include "auth.h"
#include "executor.h"

class MetricsService {
public:
    MetricsService(AuthService& auth, Executor& executor);

    void GetUsageMetrics();
private:
    AuthService& auth_;
    Executor& executor_;
};