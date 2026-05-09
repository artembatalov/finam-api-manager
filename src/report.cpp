#include "finam-api-manager/report.h"

ReportService::ReportService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}
