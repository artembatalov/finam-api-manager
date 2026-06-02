#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "finam-api-manager/client.h"
#include "finam-api-manager/executor.h"

using json = nlohmann::json;

namespace {
json Decimal(const std::string& value) {
    return json{{"value", value}};
}
}  // namespace

class MockBars : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"symbol", "SBER@MISX"},
                    {"bars",
                     json::array({json{{"timestamp", "2026-06-01T10:00:00Z"},
                                       {"open", Decimal("264.62")},
                                       {"high", Decimal("264.92")},
                                       {"low", Decimal("264.55")},
                                       {"close", Decimal("264.83")},
                                       {"volume", Decimal("1200")}}})}};
    }
};

TEST(DataService, Bars) {
    FinamSession fs(std::make_unique<MockBars>());
    std::vector<Bar> bars = fs.data.Bars("SBER@MISX", TimeFrame::kM1,
                                         Time("2026-06-01T10:00:00Z"), Time("2026-06-01T11:00:00Z"));
    ASSERT_EQ(bars.size(), 1u);
    ASSERT_EQ(bars[0].timestamp, Time("2026-06-01T10:00:00Z"));
    ASSERT_DOUBLE_EQ(bars[0].open, 264.62);
    ASSERT_DOUBLE_EQ(bars[0].high, 264.92);
    ASSERT_DOUBLE_EQ(bars[0].low, 264.55);
    ASSERT_DOUBLE_EQ(bars[0].close, 264.83);
    ASSERT_DOUBLE_EQ(bars[0].volume, 1200.0);
}

class MockQuote : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"symbol", "SBER@MISX"},
                    {"quote",
                     json{{"symbol", "SBER@MISX"},
                          {"timestamp", "2026-06-01T10:00:00Z"},
                          {"ask", Decimal("265.0")},
                          {"ask_size", Decimal("10")},
                          {"bid", Decimal("264.5")},
                          {"bid_size", Decimal("12")},
                          {"last", Decimal("264.8")},
                          {"last_size", Decimal("3")},
                          {"volume", Decimal("100000")},
                          {"open", Decimal("260.0")},
                          {"high", Decimal("266.0")},
                          {"low", Decimal("259.0")},
                          {"close", Decimal("264.8")},
                          {"change", Decimal("4.8")}}}};
    }
};

TEST(DataService, LastQuote) {
    FinamSession fs(std::make_unique<MockQuote>());
    Quote q = fs.data.LastQuote("SBER@MISX");
    ASSERT_EQ(q.symbol, "SBER@MISX");
    ASSERT_EQ(q.timestamp, Time("2026-06-01T10:00:00Z"));
    ASSERT_DOUBLE_EQ(q.ask, 265.0);
    ASSERT_DOUBLE_EQ(q.bid, 264.5);
    ASSERT_DOUBLE_EQ(q.last, 264.8);
    ASSERT_DOUBLE_EQ(q.change, 4.8);
}

class MockOrderBook : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"orderbook",
                     json{{"rows",
                           json::array({json{{"price", Decimal("265.0")}, {"sell_size", Decimal("10")}},
                                        json{{"price", Decimal("264.5")}, {"buy_size", Decimal("12")}}})}}}};
    }
};

TEST(DataService, OrderBook) {
    FinamSession fs(std::make_unique<MockOrderBook>());
    OrderBook book = fs.data.GetOrderBook("SBER@MISX");
    ASSERT_EQ(book.symbol, "SBER@MISX");
    ASSERT_EQ(book.rows.size(), 2u);
    ASSERT_DOUBLE_EQ(book.rows[0].price, 265.0);
    ASSERT_DOUBLE_EQ(book.rows[0].sell_size, 10.0);
    ASSERT_DOUBLE_EQ(book.rows[0].buy_size, 0.0);
    ASSERT_DOUBLE_EQ(book.rows[1].price, 264.5);
    ASSERT_DOUBLE_EQ(book.rows[1].buy_size, 12.0);
    ASSERT_DOUBLE_EQ(book.rows[1].sell_size, 0.0);
}

class MockLatestTrades : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"trades",
                     json::array({json{{"trade_id", "16429354800"},
                                       {"mpid", "MM1"},
                                       {"timestamp", "2026-06-01T10:00:00Z"},
                                       {"price", Decimal("264.8")},
                                       {"size", Decimal("3")},
                                       {"side", "SIDE_BUY"}}})}};
    }
};

TEST(DataService, LatestTrades) {
    FinamSession fs(std::make_unique<MockLatestTrades>());
    std::vector<LatestTrade> trades = fs.data.LatestTrades("SBER@MISX");
    ASSERT_EQ(trades.size(), 1u);
    ASSERT_EQ(trades[0].trade_id, "16429354800");
    ASSERT_EQ(trades[0].mpid, "MM1");
    ASSERT_EQ(trades[0].timestamp, Time("2026-06-01T10:00:00Z"));
    ASSERT_DOUBLE_EQ(trades[0].price, 264.8);
    ASSERT_DOUBLE_EQ(trades[0].size, 3.0);
    ASSERT_EQ(trades[0].side, "SIDE_BUY");
}
