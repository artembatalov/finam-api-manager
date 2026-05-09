#include "finam-api-manager/client.h"
#include "finam-api-manager/executor.h"

FinamSession::FinamSession(const std::string& key, Executor& executor)
	: key_(key)
	, executor_(executor)
	, auth_(key, executor)
	, account(auth_, executor)
	, metrics(auth_, executor)
	, report(auth_, executor)
	, order(auth_, executor)
	, asset(auth_, executor)
	, data(auth_, executor)
	, time(auth_, executor) {}