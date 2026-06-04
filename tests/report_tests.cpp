#include <gtest/gtest.h>

#include <nlohmann/json.hpp>

#include "finam-api-manager/client.h"
#include "finam-api-manager/executor.h"

using json = nlohmann::json;

class MockReportCreate : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"report_id", 16429354800}};
    }
};

TEST(ReportService, CreateAccountReport) {
    FinamSession fs(std::make_unique<MockReportCreate>());
    int64_t id = fs.report.CreateAccountReport(Time("2026-01-01T15:30:00Z"),
                                               Time("2026-06-01T15:30:00Z"),
                                               ReportType::kReportFormShort, 2017291);
    ASSERT_EQ(id, 16429354800);
}

class MockReportInfo : public Executor {
   public:
    json Execute(const Request& req) override {
        return json{{"info",
                     {{"report_id", 16429354800},
                      {"status", "SUCCESS"},
                      {"date_range",
                       {{"date_begin", "2026-01-01T15:30:00Z"},
                        {"date_end", "2026-06-01T15:30:00Z"}}},
                      {"report_form", "REPORT_FORM_LONG"},
                      {"account_id", 2017291},
                      {"url", "https://reports.finam.ru/16429354800.pdf"}}}};
    }
};

TEST(ReportService, GetAccountReportInfo) {
    FinamSession fs(std::make_unique<MockReportInfo>());
    ReportData rd = fs.report.GetAccountReportInfo(16429354800);
    ASSERT_EQ(rd.report_id, 16429354800);
    ASSERT_EQ(rd.account_id, 2017291);
    ASSERT_EQ(rd.status, ReportStatus::kSuccess);
    ASSERT_EQ(rd.type, ReportType::kReportFormLong);
    ASSERT_EQ(rd.date_begin, Time("2026-01-01T15:30:00Z"));
    ASSERT_EQ(rd.date_end, Time("2026-06-01T15:30:00Z"));
    ASSERT_EQ(rd.url, "https://reports.finam.ru/16429354800.pdf");
}
