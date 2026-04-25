#pragma once
#include <string>
#include <chrono>
#include "finam-api-manager/time.h"
using namespace std::chrono;

Time::Time() {
    time_ = system::clock::now();
}

Time::Time(const std::string& iso8601) {

}
