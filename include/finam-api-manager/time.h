#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Time {
public:
    using TimePoint = std::chrono::system_clock::time_point;

    Time();
    Time(const std::string& iso8601);
private:
    TimePoint time_;
};