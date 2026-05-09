#include "finam-api-manager/order.h"

OrderService::OrderService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}
