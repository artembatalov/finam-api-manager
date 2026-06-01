#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "finam-api-manager/client.h"
#include "finam-api-manager/executor.h"

using json = nlohmann::json;

std::string time_example = "2026-06-01T16:00:01Z";

class MockClock : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"timestamp", time_example}};
    }
};

TEST(AssetService, Clock) {
    FinamSession fs(std::make_unique<MockClock>());
    Time server_time = fs.asset.Clock();
    Time test_time(time_example);
    ASSERT_EQ(server_time, test_time);
}