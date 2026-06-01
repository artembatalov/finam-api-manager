#pragma once
#include <chrono>
#include <string>
#include <vector>

class Time {
   public:
    using TimePoint = std::chrono::system_clock::time_point;

    Time() = default;
    Time(const std::string& iso8601);
    std::string iso8501();
    Time now();

    auto operator<=>(const Time& other) const = default;

   private:
    TimePoint time_;
};

enum class RequestType { kGet, kPost, kPut, kPatch, kDelete };

struct Request {
    std::string url;
    RequestType type;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::vector<std::pair<std::string, std::string>> headers;
};

enum class QuoteDepth { kLast, kTop, kDepth, kUnspecified };

struct Permission {
    int delay_minutes;
    std::string mic;
    QuoteDepth quote_level;
};

struct TokenInfo {
    Time created_at;
    Time expires_at;
    std::vector<Permission> permissions;
    std::vector<int64_t> accounts;
    bool readonly;
};

struct AccountInfo {
    int64_t account_id;
    std::string type;
    std::string status;
};

// AccountService : Account

struct Cash {
    std::string currency_code;
    int64_t nanos;
    int64_t units;
};

struct PortfolioMC {
    double available_cash;
    double initial_margin;
    double maintenance_margin;
};

struct Position {
    std::string symbol;
    double average_price;
    double current_price;
    double daily_pnl;
    double quantity;
    double unrealized_pnl;
};

struct Account {
    int64_t account_id;
    std::string type;
    std::string status;

    std::vector<Cash> cash;
    double equity;

    Time first_non_trade_date;
    Time first_trade_date;
    Time open_account_date;

    PortfolioMC portfolio_mc;
    std::vector<Position> positions;
    double unrealized_profit;
};

// AccountService : Trades

struct Trade {
    int64_t account_id;
    int64_t trade_id;
    std::string symbol;
    double price;
    size_t size;
    std::string side;
    Time time;
    int64_t order_id;
    std::string comment;
};

// AccountService : Transaction

struct Change {
    std::string currency_code;
    int64_t nanos;
    int64_t units;
};

struct Transaction {
    std::string category;
    Change change;
    int64_t id;
    std::string symbol;
    Time time;
    std::string transaction_category;
    std::string transaction_name;
};

// AssetService : Asset

enum class AssetType {
    kBonds,
    kCurrencies,
    kEquities,
    kFunds,
    kFutures,
    kIndices,
    kOptions,
    kSpreads,
    kSwaps,
    kOther
};

struct Asset {
    int64_t id;
    bool is_archived;
    std::string isin;
    std::string mic;
    std::string name;
    std::string symbol;
    std::string ticker;
    AssetType type;

    void SetType(std::string type_str) {
        if (type_str == "BONDS") {
            type = AssetType::kBonds;

        } else if (type_str == "CURRENCIES") {
            type = AssetType::kCurrencies;

        } else if (type_str == "EQUITIES") {
            type = AssetType::kEquities;

        } else if (type_str == "FUNDS") {
            type = AssetType::kFunds;

        } else if (type_str == "FUTURES") {
            type = AssetType::kFutures;

        } else if (type_str == "INDICES") {
            type = AssetType::kIndices;

        } else if (type_str == "OPTIONS") {
            type = AssetType::kOptions;

        } else if (type_str == "SPREADS") {
            type = AssetType::kSpreads;

        } else if (type_str == "SWAPS") {
            type = AssetType::kSwaps;

        } else {
            type = AssetType::kOther;
        }
    }
};

// AssetService : Schedule

struct Session {
    std::string type;
    Time start;
    Time end;
};

struct Schedule {
    std::string symbol;
    std::vector<Session> sessions;
};

// AssetService : Exchanges

struct Exchange {
    std::string mic;
    std::string name;
};