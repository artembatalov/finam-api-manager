#pragma once
#include <nlohmann/json.hpp>
#include "finam-api-manager/models.h"
using json = nlohmann::json;

class IExecutor {
public:
    virtual json Execute(const Request& req) =0;
    virtual ~IExecutor() = default;
};

class CprExecutor : public IExecutor {
public:
    json Execute(const Request& req) override;
};