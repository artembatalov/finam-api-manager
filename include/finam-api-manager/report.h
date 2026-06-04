#pragma once
#include "auth.h"
#include "executor.h"

class ReportService {
   public:
    ReportService(AuthService& auth, Executor& executor);

    int64_t CreateAccountReport(Time date_begin, Time date_end, ReportType type,
                                int64_t account_id);
    ReportData GetAccountReportInfo(int64_t report_id);

   private:
    AuthService& auth_;
    Executor& executor_;
};