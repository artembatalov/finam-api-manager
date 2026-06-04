#pragma once
#include "auth.h"
#include "executor.h"
#include "models.h"

class MetricsService {
   public:
    MetricsService(AuthService& auth, Executor& executor);

    UsageMetrics GetUsageMetrics();

   private:
    AuthService& auth_;
    Executor& executor_;
};
