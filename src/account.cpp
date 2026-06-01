#include "finam-api-manager/account.h"

#include <string>

AccountService::AccountService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}

Account AccountService::GetAccount(int64_t account_id) {
    Request req = {.url = "https://api.finam.ru/v1/accounts/" + std::to_string(account_id),
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    Account account;
    account.account_id = res["account_id"];
    for (auto& c : res["cash"]) {
        Cash cash{.currency_code = c["currency_code"],
                  .nanos = std::stoll(c["nanos"].get<std::string>()),
                  .units = std::stoi(c["units"].get<std::string>())};
        account.cash.push_back(cash);
    }
    // ...
    return account;
}

std::vector<Trade> AccountService::Trades(int64_t account_id, size_t limit, Time start, Time end) {
    // function params must be optional
    Request req = {
        .url = "https://api.finam.ru/v1/accounts/" + std::to_string(account_id) + "/trades/",
        .type = RequestType::kGet,
        .parameters = {{"limit", "15"},
                       {"interval.start_time", start.iso8501()},
                       {"interval.end_time", end.iso8501()}},
        .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::vector<Trade> trades;
    for (auto& t : res["trades"]) {
        Trade trade{.account_id = std::stoll(t["account_id"].get<std::string>()),
                    .trade_id = std::stoll(t["trade_id"].get<std::string>()),
                    .symbol = t["symbol"],
                    .price = t["price"]["value"].get<double>(),
                    .size = t["size"]["value"].get<size_t>(),
                    .side = t["side"],
                    .time = Time(t["timestamp"]),
                    .order_id = t["order_id"].get<int64_t>(),
                    .comment = t["comment"]};
        trades.push_back(trade);
    }
    return trades;
}

std::vector<Transaction> AccountService::Transactions(int64_t account_id, size_t limit, Time start,
                                                      Time end) {
    // function params must be optional
    Request req = {
        .url = "https://api.finam.ru/v1/accounts/" + std::to_string(account_id) + "/trades/",
        .type = RequestType::kGet,
        .parameters = {{"limit", "15"},
                       {"interval.start_time", start.iso8501()},
                       {"interval.end_time", end.iso8501()}},
        .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::vector<Transaction> transactions;
    for (auto& t : res["trades"]) {
        // Trade trade{.account_id = std::stoll(t["account_id"].get<std::string>()),
        //             .trade_id = std::stoll(t["trade_id"].get<std::string>()),
        //             .symbol = t["symbol"],
        //             .price = t["price"]["value"].get<double>(),
        //             .size = t["size"]["value"].get<size_t>(),
        //             .side = t["side"],
        //             .time = Time(t["timestamp"]),
        //             .order_id = t["order_id"].get<int64_t>(),
        //             .comment = t["comment"]};
        // transactions.push_back(trade);
    }
    return transactions;
}