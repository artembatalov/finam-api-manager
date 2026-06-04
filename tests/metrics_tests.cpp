#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "finam-api-manager/client.h"
#include "finam-api-manager/executor.h"

using json = nlohmann::json;

class MockUsage : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"quotas",
                     json::array({json{{"name", "GetQuote"},
                                       {"limit", "200"},
                                       {"remaining", "187"},
                                       {"reset_time", "2026-06-01T10:01:00Z"}},
                                  json{{"name", "Bars"},
                                       {"limit", "100"},
                                       {"remaining", "100"},
                                       {"reset_time", "2026-06-01T10:01:00Z"}}})}};
    }
};

TEST(MetricsService, GetUsageMetrics) {
    FinamSession fs(std::make_unique<MockUsage>());
    UsageMetrics metrics = fs.metrics.GetUsageMetrics();
    ASSERT_EQ(metrics.quotas.size(), 2u);

    ASSERT_EQ(metrics.quotas[0].name, "GetQuote");
    ASSERT_EQ(metrics.quotas[0].limit, 200);
    ASSERT_EQ(metrics.quotas[0].remaining, 187);
    ASSERT_EQ(metrics.quotas[0].reset_time, Time("2026-06-01T10:01:00Z"));

    ASSERT_EQ(metrics.quotas[1].name, "Bars");
    ASSERT_EQ(metrics.quotas[1].limit, 100);
    ASSERT_EQ(metrics.quotas[1].remaining, 100);
}
