#include <iostream>

#include "finam-api-manager/client.h"

int main() {
    FinamSession session("key");

    UsageMetrics metrics = session.metrics.GetUsageMetrics();
    std::cout << "Quotas: " << metrics.quotas.size() << "\n";
    for (const Quota& q : metrics.quotas) {
        std::cout << "  " << q.name << ": " << q.remaining << "/" << q.limit << " left, resets at "
                  << q.reset_time.iso8501() << "\n";
    }
}
