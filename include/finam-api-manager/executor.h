#pragma once
#include <nlohmann/json.hpp>
#include "finam-api-manager/models.h"
using json = nlohmann::json;

class Executor {
public:
    virtual json Execute(const Request& req) =0;
    virtual ~Executor() = default;
};

class CprExecutor : public Executor {
public:
    json Execute(const Request& req) override;
};