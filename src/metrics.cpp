#include "finam-api-manager/metrics.h"

MetricsService::MetricsService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}

UsageMetrics MetricsService::GetUsageMetrics() {
    Request req = {.url = "https://api.finam.ru/v1/usage",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    UsageMetrics metrics;
    for (auto& q : res["quotas"]) {
        Quota quota{.name = q["name"].get<std::string>(),
                    .limit = std::stoll(q["limit"].get<std::string>()),
                    .remaining = std::stoll(q["remaining"].get<std::string>()),
                    .reset_time = Time(q["reset_time"].get<std::string>())};
        metrics.quotas.push_back(quota);
    }
    return metrics;
}
