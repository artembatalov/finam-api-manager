#include <string>
#include <chrono>
#include <sstream>
#include <date/date.h>
#include "finam-api-manager/time.h"
using namespace std::chrono;

Time::Time(const std::string& iso8601) {
    std::istringstream ss{iso8601};
    date::from_stream(ss, "%FT%TZ", time_);
}

std::string Time::iso8501() {
    return std::format("{:%FT%TZ}", std::chrono::time_point_cast<std::chrono::seconds>(time_));
}

Time Time::now() {
    TimePoint time = std::chrono::system_clock::now();
    Time now;
    now.time_ = time;
    return now;
}
