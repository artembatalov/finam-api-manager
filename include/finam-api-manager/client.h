#pragma once
#include <cpr/cpr.h>
#include <memory.h>

#include <nlohmann/json.hpp>
#include <string>

#include "account.h"
#include "asset.h"
#include "auth.h"
#include "data.h"
#include "executor.h"
#include "metrics.h"
#include "order.h"
#include "report.h"
#include "time.h"
using json = nlohmann::json;

class FinamSession {
   public:
    explicit FinamSession(const std::string& key)
        : FinamSession(key, std::make_unique<CprExecutor>()) {}

    FinamSession(std::unique_ptr<Executor> executor);

   private:
    FinamSession(const std::string& key, std::unique_ptr<Executor> executor);
    std::string key_;
    std::unique_ptr<Executor> executor_;
    AuthService auth_;

   public:
    AccountService account;
    MetricsService metrics;
    ReportService report;
    OrderService order;
    AssetService asset;
    DataService data;
};