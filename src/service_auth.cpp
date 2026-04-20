#include "finam-api-manager/service_auth.h"
#include "finam-api-manager/models.h"
#include <nlohmann/json.hpp>
#include <cstdint>
#include <stdexcept>
#include <string>
using json = nlohmann::json;

AuthService::AuthService(const std::string& key, IExecutor& executor)
    : key_(key), executor_(executor) {
    Auth();
    TokenDetails();
}

std::string AuthService::GetToken() {
    if (InvalidToken()) {
        Auth();
        TokenDetails();
    }
    return token_;
}

std::vector<int64_t> AuthService::GetAccountIds() const {
    return info_.accounts;
}

QuoteDepth DefineQuoteLevel(const std::string& level) {
    if (level == "QUOTE_LEVEL_LAST") {
        return QuoteDepth::kLast;
    }
    else if (level == "QUOTE_LEVEL_TOP_OF_BOOK") {
        return QuoteDepth::kTop;
    }
    else if (level == "QUOTE_LEVEL_DEPTH_OF_MARKET") {
        return QuoteDepth::kDepth;
    }
    else {
        return QuoteDepth::kUnspecified;
    }
}

void AuthService::Auth() {
    Request req = {
        .url = "https://api.finam.ru/v1/sessions",
        .type = RequestType::kPost,
        .parameters = {{"secret", key_}},
        .headers = {{"Content-Type", "application/json"}}
    };
    auto res = executor_.Execute(req);
    token_ = res["token"];
}

void AuthService::TokenDetails() {
    Request req = {
        .url = "https://api.finam.ru/v1/sessions/details",
        .type = RequestType::kPost,
        .parameters = {{"token", token_}},
        .headers = {{"Content-Type", "application/json"}}
    };
    auto res = executor_.Execute(req);
    info_.created_at = res["created_at"];
    info_.expires_at = res["expires_at"];
    info_.readonly = res["readonly"];
    for (size_t i = 0; i < res["account_ids"].size(); i++) {
        int64_t account = std::stoll(res["account_ids"][i].get<std::string>());
        info_.accounts.push_back(account);
    }
    for (size_t i = 0; i < res["md_permissions"]; i++) {
        Permission permission = {
            .delay_minutes = res["md_permissions"][i]["delay_minutes"],
            .mic = res["md_permissions"][i]["mic"],
            .quote_level = DefineQuoteLevel(res["md_permissions"][i]["quote_level"])
        };
        info_.permissions.push_back(permission);
    }
}

bool AuthService::InvalidToken() {
    return false;
}
