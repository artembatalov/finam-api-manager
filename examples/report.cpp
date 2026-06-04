#include <iostream>

#include "finam-api-manager/client.h"

int main() {
    FinamSession session("key");

    // 1. Request an account report for a date range.
    int64_t report_id = session.report.CreateAccountReport(Time("2026-01-01T15:30:00Z"),
                                                           Time("2026-06-01T15:30:00Z"),
                                                           ReportType::kReportFormShort, 2017291);
    std::cout << "Created report, id = " << report_id << "\n";

    // 2. Poll its status; the URL is filled in once the report is ready.
    ReportData info = session.report.GetAccountReportInfo(report_id);
    std::cout << "Form: " << ReportTypeToString(info.type) << "\n";
    std::cout << "From: " << info.date_begin.iso8501() << "\n";
    std::cout << "To:   " << info.date_end.iso8501() << "\n";
    std::cout << "URL:  " << info.url << "\n";
}
