#include <string>
#include "finam-api-manager/service_time.h"
#include "finam-api-manager/executor.h"

TimeService::TimeService(AuthService& auth, IExecutor& executor)
    : auth_(auth), executor_(executor) {}


std::string TimeService::ServerTime(const std::string& account_id) {
    Request req = {
        .url = "https://api.finam.ru/v1/accounts/" + account_id,
        .type = RequestType::kGet,
        .parameters = {},
        .headers = {{"Authorization", "Bearer " + auth_.GetToken()}},
    };
    auto res = executor_.Execute(req);
    return res["timestamp"];
}