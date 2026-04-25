#include <iostream>
#include <chrono>
#include <format>
#include "date/tz.h"

int main() {
    std::cout << "It works!" << std::endl;
    using namespace std::chrono;

    auto now = system_clock::now();

    auto zt = date::make_zoned("UTC", now);

    std::cout << date::format("%F %T %Z", zt) << "\n";
    return 0;
}