#include "finam-api-manager/report.h"

#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

ReportService::ReportService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}

int64_t ReportService::CreateAccountReport(Time date_begin, Time date_end, ReportType type,
                                           int64_t account_id) {
    json body;
    body["date_range"]["date_begin"] = date_begin.iso8501();
    body["date_range"]["date_end"] = date_end.iso8501();
    body["report_form"] = ReportTypeToString(type);
    body["account_id"] = std::to_string(account_id);
    Request req = {.url = "https://api.finam.ru/v1/report",
                   .type = RequestType::kPost,
                   .body = body,
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()},
                               {"Content-Type", "application/json"}}};
    auto res = executor_.Execute(req);
    std::cout << res.dump(4);
    return res["report_id"].get<int64_t>();
}

ReportData ReportService::GetAccountReportInfo(int64_t report_id) {
    Request req = {.url = "https://api.finam.ru/v1/report/" + std::to_string(report_id) + "/info",
                   .type = RequestType::kGet,
                   .headers = {{"Authorization", "Bearer " + auth_.GetToken()},
                               {"Content-Type", "application/json"}}};
    auto res = executor_.Execute(req);
    ReportData rd;
    rd.report_id = res["info"]["report_id"].get<int64_t>();
    rd.status = StringToStatus(res["info"]["status"].get<std::string>());
    rd.date_begin = Time(res["info"]["date_range"]["date_begin"].get<std::string>());
    rd.date_end = Time(res["info"]["date_range"]["date_end"].get<std::string>());
    rd.type = StringToReportType(res["info"]["report_form"].get<std::string>());
    rd.account_id = res["info"]["account_id"].get<int64_t>();
    rd.url = res["info"]["url"].get<std::string>();
    return rd;
}