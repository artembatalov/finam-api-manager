#pragma once
#include <string>
#include <vector>
#include <chrono>

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

enum class RequestType {kGet, kPost, kPut, kPatch, kDelete};

struct Request {
    std::string url;
    RequestType type;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::vector<std::pair<std::string, std::string>> headers;
};

enum class QuoteDepth {kLast, kTop, kDepth, kUnspecified};

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