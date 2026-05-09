#include "finam-api-manager/metrics.h"

MetricsService::MetricsService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}
