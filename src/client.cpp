#include "finam-api-manager/client.h"

#include <string>

#include "finam-api-manager/executor.h"

FinamSession::FinamSession(const std::string& key, std::unique_ptr<Executor> executor)
    : key_(key),
      executor_(std::move(executor)),
      auth_(key, *executor_),
      account(auth_, *executor_),
      metrics(auth_, *executor_),
      report(auth_, *executor_),
      order(auth_, *executor_),
      asset(auth_, *executor_),
      data(auth_, *executor_) {}

FinamSession::FinamSession(std::unique_ptr<Executor> executor)
    : key_(""),
      executor_(std::move(executor)),
      auth_(*executor_),
      account(auth_, *executor_),
      metrics(auth_, *executor_),
      report(auth_, *executor_),
      order(auth_, *executor_),
      asset(auth_, *executor_),
      data(auth_, *executor_){}