#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <stdexcept>
#include "finam-trade-api/executor.h"
#include "finam-trade-api/models.h"
using json = nlohmann::json;

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
