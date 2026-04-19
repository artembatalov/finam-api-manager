#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <stdexcept>
#include "finam-api-manager/executor.h"
#include "finam-api-manager/models.h"
using json = nlohmann::json;

void CheckStatus(int32_t status_code) {
    switch(status_code) {
        case 200: {
            return;
        }
        case 401: {
            throw std::runtime_error("GetJwtToken: 401 Token has expired or the token is invalid!");
        }
        case 404: {
            throw std::runtime_error("GetJwtToken: 404 Account not found in token!");
        }
        case 429: {
            throw std::runtime_error("GetJwtToken: 429 Too many requests. The available limit is 200 requests per minute!");
        }
        case 500: {
            throw std::runtime_error("GetJwtToken: 500 Internal Service Error. Please try again later!");
        }
        case 503: {
            throw std::runtime_error("GetJwtToken: 503 Service is currently unavailable. Please try again later!");
        }
        case 504: {
            throw std::runtime_error("GetJwtToken: 504 The deadline expired before the operation was completed!");
        }
        default: {
            throw std::runtime_error("GetJwtToken: default An unexpected error response!");
        }
    }
}

cpr::Url GetUrl(const Request& req) {
    return cpr::Url{req.url};
}

cpr::Header GetHeaders(const Request& req) {
    cpr::Header headers;
    for (auto& pair : req.headers) {
        headers[pair.first] = pair.second;
    }
    return headers;
}

cpr::Parameters GetParameters(const Request& req) {
    cpr::Parameters parameters;
    for (auto& pair : req.parameters) {
        parameters.Add({pair.first, pair.second});
    }
}

json ExecuteGet(const Request& req) {
    cpr::Response r = cpr::Get(
        GetUrl(req),
        GetHeaders(req),
        GetParameters(req)
    );
    CheckStatus(r.status_code);
    return json::parse(r.text);
}

json ExecutePost(const Request& req) {
    cpr::Response r = cpr::Post(
        GetUrl(req),
        GetHeaders(req),
        GetParameters(req)
    );
    return json::parse(r.text);
}

json ExecutePut(const Request& req) {
    cpr::Response r = cpr::Put(
        GetUrl(req),
        GetHeaders(req),
        GetParameters(req)
    );
    return json::parse(r.text);
}

json ExecutePatch(const Request& req) {
    cpr::Response r = cpr::Patch(
        GetUrl(req),
        GetHeaders(req),
        GetParameters(req)
    );
    return json::parse(r.text);
}

json ExecuteDelete(const Request& req) {
    cpr::Response r = cpr::Delete(
        GetUrl(req),
        GetHeaders(req),
        GetParameters(req)
    );
    return json::parse(r.text);
}

json CprExecutor::Execute(const Request& req) {
    switch (req.type) {
        case RequestType::kGet:
            return ExecuteGet(req);
        case RequestType::kPost:
            return ExecutePost(req);
        case RequestType::kPut:
            return ExecutePut(req);
        case RequestType::kPatch:
            return ExecutePatch(req);
        case RequestType::kDelete:
            return ExecuteDelete(req);
        default:
            throw std::runtime_error("CprExecutor::Execute: Undefined request type");
    }
}

