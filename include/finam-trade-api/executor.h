#pragma once
#include <nlohmann/json.hpp>
#include "finam-trade-api/models.h"
using json = nlohmann::json;

class IExecutor {
public:
    virtual json Execute(const Request& req) =0;
    virtual ~IExecutor() =0;
};

class CprExecutor : public IExecutor {
public:
    json Execute(const Request& req) override;
};