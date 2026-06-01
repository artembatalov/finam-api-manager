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
| `session.data` | Bars, order book, quotes | Stub |
| `session.order` | Place / cancel orders | Stub |
| `session.metrics` | API usage metrics | Stub |
| `session.report` | Account reports | Stub |
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

### TimeService

```cpp
std::string srv  = session.time.ServerTime(account_id);
std::string local = session.time.MachineTime();
```

## Authentication

`AuthService` is internal and not exposed to callers. Authentication happens lazily on the first service call: the library exchanges your API key for a JWT via `POST /v1/sessions`, fetches token details, and caches the token until expiry.

## Links

- [Official Finam Trade API docs](https://tradeapi.finam.ru/docs/rest)
