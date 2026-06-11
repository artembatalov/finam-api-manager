#include <string>
#include <chrono>
#include <sstream>
#include <date/date.h>
#include "finam-api-manager/models.h"
using namespace std::chrono;

Time::Time(const std::string& iso8601) {
    std::istringstream ss{iso8601};
    date::sys_time<std::chrono::nanoseconds> tp;
    ss >> date::parse("%FT%TZ", tp);
    time_ = std::chrono::time_point_cast<TimePoint::duration>(tp);
}

std::string Time::iso8501() const {
    return std::format("{:%FT%TZ}", std::chrono::time_point_cast<std::chrono::seconds>(time_));
}

Time Time::now() {
    TimePoint time = std::chrono::system_clock::now();
    Time now;
    now.time_ = time;
    return now;
}

std::string ReportTypeToString(ReportType type) {
    if (type == ReportType::kReportFormLong) {
        return "REPORT_FORM_LONG";
    } else if (type == ReportType::kReportFormShort) {
        return "REPORT_FORM_SHORT";
    } else {
        return "REPORT_FORM_UNKNOWN";
    }
}

ReportType StringToReportType(std::string type) {
    if (type == "REPORT_FORM_LONG") {
        return ReportType::kReportFormLong;
    } else if (type == "REPORT_FORM_SHORT") {
        return ReportType::kReportFormShort;
    } else {
        return ReportType::kReportFormUnknown;
    }
}

ReportStatus StringToStatus(std::string str) {
    if (str == "NOT_FOUND") {
        return ReportStatus::kNotFound;
    } else if (str == "PENDING") {
        return ReportStatus::kPending;
    } else if (str == "IN_PROGRESS") {
        return ReportStatus::kInProgress;
    } else if (str == "SUCCESS") {
        return ReportStatus::kSuccess;
    } else {
        return ReportStatus::kError;
    }
}

std::string TimeFrameToString(TimeFrame timeframe) {
    switch (timeframe) {
        case TimeFrame::kM1:
            return "TIME_FRAME_M1";
        case TimeFrame::kM5:
            return "TIME_FRAME_M5";
        case TimeFrame::kM15:
            return "TIME_FRAME_M15";
        case TimeFrame::kM30:
            return "TIME_FRAME_M30";
        case TimeFrame::kH1:
            return "TIME_FRAME_H1";
        case TimeFrame::kH2:
            return "TIME_FRAME_H2";
        case TimeFrame::kH4:
            return "TIME_FRAME_H4";
        case TimeFrame::kH8:
            return "TIME_FRAME_H8";
        case TimeFrame::kD:
            return "TIME_FRAME_D";
        case TimeFrame::kW:
            return "TIME_FRAME_W";
        case TimeFrame::kMN:
            return "TIME_FRAME_MN";
        case TimeFrame::kQR:
            return "TIME_FRAME_QR";
        default:
            return "TIME_FRAME_UNSPECIFIED";
    }
}
