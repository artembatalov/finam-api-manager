#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include "executor.h"
#include "account.h"
#include "asset.h"
#include "auth.h"
#include "data.h"
#include "metrics.h"
#include "order.h"
#include "report.h"
#include "time.h"
using json = nlohmann::json;

class FinamSession {
public:
	FinamSession(const std::string& key, Executor& executor);

	AccountService account;
	MetricsService metrics;
	ReportService  report;
	OrderService   order;
	AssetService   asset;
	DataService    data;
	TimeService    time;

private:
	std::string key_;
	Executor& executor_;
	AuthService auth_;
};