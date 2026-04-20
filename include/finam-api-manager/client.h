#pragma once

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include "executor.h"
#include "service_account.h"
#include "service_asset.h"
#include "service_auth.h"
#include "service_data.h"
#include "service_metrics.h"
#include "service_order.h"
#include "service_report.h"
#include "service_time.h"
using json = nlohmann::json;

class FinamApiClient {
public:
	FinamApiClient(const std::string& key, IExecutor& executor)
		: key_(key)
		, executor_(executor)
		, auth_(key, executor)
		, time_(auth_, executor){}

	// Account service
	void GetAccount();
	void Trades();
	void Transactions();

	// Orders service
	void GetOrders();
	void PlaceOrder();
	void GetOrder();
	void CancelOrder();
	void PlaceSLTPOrder();

	// Market data service
	void Bars();
	void OrderBook();
	void LastQuote();
	void LatestTrades();

	// Asset service
	void Assets();
	void AllAssets();
	std::string Clock();
	void GetAsset();
	void GetConstituents();
	void GetAssetParams();
	void Schedule();
	void OptionsChain();
	void Exchanges();

	// Usage metrics service
	void GetUsageMetrics();

	// Report service
	void CreateAccountReport();
	void GetAccountReportInfo();

private:
	std::string key_;
	IExecutor& executor_;

	AccountService account_;
	AssetService asset_;
	AuthService auth_;
	DataService data_;
	MetricsService metrics_;
	OrderService order_;
	ReportService report_;
	TimeService time_;
};