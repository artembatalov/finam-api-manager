#include "finam-api-manager/account.h"

AccountService::AccountService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}