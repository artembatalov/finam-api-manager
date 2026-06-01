#include "finam-api-manager/client.h"

#include <string>

#include "finam-api-manager/executor.h"

FinamSession::FinamSession(const std::string& key, std::unique_ptr<Executor> executor)
    : key_(key),
      executor_(std::move(executor)),
      auth_(key, *executor),
      account(auth_, *executor),
      metrics(auth_, *executor),
      report(auth_, *executor),
      order(auth_, *executor),
      asset(auth_, *executor),
      data(auth_, *executor),
      time(auth_, *executor) {}

FinamSession::FinamSession(std::unique_ptr<Executor> executor)
    : key_(""),
      executor_(std::move(executor)),
      auth_(*executor),
      account(auth_, *executor),
      metrics(auth_, *executor),
      report(auth_, *executor),
      order(auth_, *executor),
      asset(auth_, *executor),
      data(auth_, *executor),
      time(auth_, *executor) {}