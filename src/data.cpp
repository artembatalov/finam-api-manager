#include "finam-api-manager/data.h"

#include <string>

namespace {

// Finam wraps decimal values as {"value": "264.62"} (a string). Pull it out as a double.
double Decimal(const json& field) {
    return std::stod(field["value"].get<std::string>());
}

}  // namespace

DataService::DataService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}

std::vector<Bar> DataService::Bars(const std::string& symbol, TimeFrame timeframe, Time start,
                                   Time end) {
    Request req = {.url = "https://api.finam.ru/v1/instruments/" + symbol + "/bars",
                   .type = RequestType::kGet,
                   .parameters = {{"timeframe", TimeFrameToString(timeframe)},
                                  {"interval.start_time", start.iso8501()},
                                  {"interval.end_time", end.iso8501()}},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::vector<Bar> bars;
    for (auto& b : res["bars"]) {
        Bar bar{.timestamp = Time(b["timestamp"].get<std::string>()),
                .open = Decimal(b["open"]),
                .high = Decimal(b["high"]),
                .low = Decimal(b["low"]),
                .close = Decimal(b["close"]),
                .volume = Decimal(b["volume"])};
        bars.push_back(bar);
    }
    return bars;
}

Quote DataService::LastQuote(const std::string& symbol) {
    Request req = {.url = "https://api.finam.ru/v1/instruments/" + symbol + "/quotes/latest",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    auto& q = res["quote"];
    Quote quote{.symbol = q["symbol"].get<std::string>(),
                .timestamp = Time(q["timestamp"].get<std::string>()),
                .ask = Decimal(q["ask"]),
                .ask_size = Decimal(q["ask_size"]),
                .bid = Decimal(q["bid"]),
                .bid_size = Decimal(q["bid_size"]),
                .last = Decimal(q["last"]),
                .last_size = Decimal(q["last_size"]),
                .volume = Decimal(q["volume"]),
                .open = Decimal(q["open"]),
                .high = Decimal(q["high"]),
                .low = Decimal(q["low"]),
                .close = Decimal(q["close"]),
                .change = Decimal(q["change"])};
    return quote;
}

OrderBook DataService::GetOrderBook(const std::string& symbol) {
    Request req = {.url = "https://api.finam.ru/v1/instruments/" + symbol + "/orderbook",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    OrderBook book{.symbol = symbol};
    for (auto& r : res["orderbook"]["rows"]) {
        OrderBookRow row{.price = Decimal(r["price"]),
                         .sell_size = r.contains("sell_size") ? Decimal(r["sell_size"]) : 0.0,
                         .buy_size = r.contains("buy_size") ? Decimal(r["buy_size"]) : 0.0};
        book.rows.push_back(row);
    }
    return book;
}

std::vector<LatestTrade> DataService::LatestTrades(const std::string& symbol) {
    Request req = {.url = "https://api.finam.ru/v1/instruments/" + symbol + "/trades/latest",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::vector<LatestTrade> trades;
    for (auto& t : res["trades"]) {
        LatestTrade trade{.trade_id = t["trade_id"].get<std::string>(),
                          .mpid = t.contains("mpid") ? t["mpid"].get<std::string>() : "",
                          .timestamp = Time(t["timestamp"].get<std::string>()),
                          .price = Decimal(t["price"]),
                          .size = Decimal(t["size"]),
                          .side = t["side"].get<std::string>()};
        trades.push_back(trade);
    }
    return trades;
}
