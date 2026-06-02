#include <iostream>

#include "finam-api-manager/client.h"

int main() {
    FinamSession session("key");

    const std::string symbol = "SBER@MISX";

    // 1. Historical candles (1-minute bars over an hour).
    std::vector<Bar> bars = session.data.Bars(symbol, TimeFrame::kM1, Time("2026-06-01T10:00:00Z"),
                                              Time("2026-06-01T11:00:00Z"));
    std::cout << "Bars: " << bars.size() << "\n";
    if (!bars.empty()) {
        std::cout << "  first close = " << bars.front().close << "\n";
    }

    // 2. Latest quote.
    Quote q = session.data.LastQuote(symbol);
    std::cout << "Quote: bid " << q.bid << " / ask " << q.ask << " (last " << q.last << ")\n";

    // 3. Order book.
    OrderBook book = session.data.GetOrderBook(symbol);
    std::cout << "Order book rows: " << book.rows.size() << "\n";

    // 4. Latest trades.
    std::vector<LatestTrade> trades = session.data.LatestTrades(symbol);
    std::cout << "Latest trades: " << trades.size() << "\n";
}
