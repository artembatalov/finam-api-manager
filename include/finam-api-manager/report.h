#pragma once
#include "auth.h"
#include "executor.h"

class ReportService {
public:
    ReportService(AuthService& auth, Executor& executor);

    void CreateAccountReport();
    void GetAccountReportInfo();
private:
    AuthService& auth_;
    Executor& executor_;
};