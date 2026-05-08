#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Time {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    Time() = default;
    Time(const std::string& iso8601);
    std::string iso8501();
    Time now();

    auto operator<=>(const Time& other) const = default;
private:
    TimePoint time_;
};