#include "finam-api-manager/asset.h"

AssetService::AssetService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}

std::vector<Asset> AssetService::Assets() {
    Request req = {.url = "https://api.finam.ru/v1/assets/",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::vector<Asset> assets;
    for (auto& a : res["assets"]) {
        Asset asset{.id = a["id"].get<int64_t>(),
                    .is_archived = a["is_archived"].get<bool>(),
                    .isin = a["isin"].get<std::string>(),
                    .mic = a["mic"].get<std::string>(),
                    .name = a["name"].get<std::string>(),
                    .symbol = a["symbol"].get<std::string>(),
                    .ticker = a["ticker"].get<std::string>()};
        asset.SetType(a["type"].get<std::string>());
        assets.push_back(asset);
    }
    return assets;
}

std::vector<Asset> AssetService::AllAssets(std::string cursor, bool only_active,
                                           bool only_disabled) {
    // to do
    Request req = {.url = "https://api.finam.ru/v1/assets/",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::vector<Asset> assets;
    for (auto& a : res["assets"]) {
        Asset asset{.id = a["id"].get<int64_t>(),
                    .is_archived = a["is_archived"].get<bool>(),
                    .isin = a["isin"].get<std::string>(),
                    .mic = a["mic"].get<std::string>(),
                    .name = a["name"].get<std::string>(),
                    .symbol = a["symbol"].get<std::string>(),
                    .ticker = a["ticker"].get<std::string>()};
        asset.SetType(a["type"].get<std::string>());
        assets.push_back(asset);
    }
    return assets;
}

Time AssetService::Clock() {
    Request req = {.url = "https://api.finam.ru/v1/assets/clock",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::string time_str = res["timestamp"].get<std::string>();
    Time time(time_str);
    return time;
}

Schedule AssetService::GetSchedule(std::string symbol) {
    Request req = {.url = "https://api.finam.ru/v1/assets/" + symbol + "/schedule",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    Schedule schedule{.symbol = res["symbol"].get<std::string>()};
    for (auto& s : res["sessions"]) {
        Session session{
            .type = s["type"].get<std::string>(),
            .start = Time(s["interval"]["start_time"].get<std::string>()),
            .end = Time(s["interval"]["end_time"].get<std::string>()),
        };
        schedule.sessions.push_back(session);
    }
    return schedule;
}

std::vector<Exchange> AssetService::Exchanges() {
    Request req = {.url = "https://api.finam.ru/v1/exchanges",
                   .type = RequestType::kGet,
                   .parameters = {},
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()}}};
    auto res = executor_.Execute(req);
    std::vector<Exchange> exchanges;
    for (auto& e : res["exchanges"]) {
        Exchange exchange{.mic = e["mic"].get<std::string>(), .name = e["name"].get<std::string>()};
        exchanges.push_back(exchange);
    }
    return exchanges;
}