#include "finam-api-manager/data.h"

DataService::DataService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}
