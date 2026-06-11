# finam-api-manager

> **Unofficial** C++20 library for the [Finam Trade API (REST)](https://tradeapi.finam.ru/docs/rest). Under active development — API may change.

## Quick start

```cpp
#include "finam-api-manager/client.h"

int main() {
    FinamSession session("your-api-key");

    // Authentication is lazy — happens on the first service call
    Time server_time = session.asset.Clock();
    std::cout << server_time.iso8501() << "\n";
}
```

`FinamSession` owns its HTTP executor and auth internally. You only need your API key.

## Building

Requires CMake 3.20+ and libcurl.

```bash
# Ubuntu
sudo apt-get install -y libcurl4-openssl-dev

# Configure & build
cmake -B build
cmake --build build

# Run tests
ctest --test-dir build --output-on-failure
```

Build options (all enabled by default):

| Option | Description |
|---|---|
| `-DENABLE_TESTS=OFF` | Skip tests |
| `-DENABLE_EXAMPLES=OFF` | Skip examples |
| `-DENABLE_INTERNAL=OFF` | Skip internal/scratch targets |

## Services

All services are accessed as public members of `FinamSession`.

| Member | Service | Status |
|---|---|---|
| `session.account` | Portfolio, trades, transactions | In progress |
| `session.asset` | Assets, exchanges, schedules | In progress |
| `session.data` | Bars, quotes, order book, trades | In progress |
| `session.order` | Place / cancel orders | Stub |
| `session.metrics` | API usage metrics | In progress |
| `session.report` | Account reports | In progress |
| `session.time` | Server / machine time | In progress |

### AccountService

```cpp
Account acc = session.account.GetAccount(account_id);
std::vector<Trade> trades = session.account.Trades(account_id, 50, from, to);
std::vector<Transaction> txns = session.account.Transactions(account_id, 50, from, to);
```

### AssetService

```cpp
std::vector<Asset> assets  = session.asset.Assets();
std::vector<Exchange> exch = session.asset.Exchanges();
Schedule sched             = session.asset.GetSchedule("SBER@MISX");
Time server_time           = session.asset.Clock();
```

### DataService (market data)

```cpp
std::vector<Bar> bars = session.data.Bars("SBER@MISX", TimeFrame::kM1,
                                          Time("2026-06-01T10:00:00Z"),
                                          Time("2026-06-01T11:00:00Z"));
Quote q                 = session.data.LastQuote("SBER@MISX");
OrderBook book          = session.data.GetOrderBook("SBER@MISX");
std::vector<LatestTrade> trades = session.data.LatestTrades("SBER@MISX");
```

`TimeFrame` covers `kM1`–`kM30`, `kH1`–`kH8`, `kD`, `kW`, `kMN`, `kQR`.

### MetricsService

```cpp
UsageMetrics metrics = session.metrics.GetUsageMetrics();
for (const Quota& q : metrics.quotas) {
    // q.name, q.limit, q.remaining, q.reset_time
}
```

### ReportService

```cpp
int64_t report_id = session.report.CreateAccountReport(
    Time("2026-01-01T15:30:00Z"), Time("2026-06-01T15:30:00Z"),
    ReportType::kReportFormShort, account_id);

ReportData info = session.report.GetAccountReportInfo(report_id);
// info.status, info.type, info.date_begin, info.date_end, info.url
```

### TimeService

```cpp
std::string srv  = session.time.ServerTime(account_id);
std::string local = session.time.MachineTime();
```

## Authentication

`AuthService` is internal and not exposed to callers. Authentication happens lazily on the first service call: the library exchanges your API key for a JWT via `POST /v1/sessions`, fetches token details, and caches the token until expiry.

## Links

- [Official Finam Trade API docs](https://tradeapi.finam.ru/docs/rest)
