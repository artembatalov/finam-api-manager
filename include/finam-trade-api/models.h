#pragma once
#include <string>
#include <vector>

enum class RequestType {kGet, kPost, kPut, kPatch, kDelete};

struct Request {
    std::string url;
    RequestType type;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::vector<std::pair<std::string, std::string>> headers;
};