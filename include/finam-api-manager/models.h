#pragma once
#include <string>
#include <vector>
#include "time.h"

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