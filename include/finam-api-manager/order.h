#pragma once
#include "auth.h"
#include "executor.h"

class OrderService {
public:
    OrderService(AuthService& auth, Executor& executor);

    void GetOrders();
    void PlaceOrder();
    void GetOrder();
    void CancelOrder();
    void PlaceSLTPOrder();
private:
    AuthService& auth_;
    Executor& executor_;
};