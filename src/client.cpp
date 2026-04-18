#include "finam-trade-api/client.h"
#include "finam-trade-api/models.h"

void FinamApiClient::Auth() {
    Request req = {
        .url = "https://api.finam.ru/v1/sessions",
        .type = RequestType::kPost,
        .parameters = {{"secret", key_}},
        .headers = {{"Content-Type", "application/json"}},
    };
    auto res = executor_.Execute(req);
    jwt_ = res["token"];
}