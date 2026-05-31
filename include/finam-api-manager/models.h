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

struct Transaction {};