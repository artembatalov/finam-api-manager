#pragma once

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <stdexcept>
using json = nlohmann::json;


class FinamApiClient {
public:
	FinamApiClient(const std::string& key)
		: key_(key) {}

	// Authentification service
	void TokenDetails();

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
	void Clock();
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
	void Auth();
	std::string jwt_;
	std::string key_;
};