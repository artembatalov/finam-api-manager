#include "finam-api-manager/asset.h"

AssetService::AssetService(AuthService& auth, Executor& executor)
    : auth_(auth), executor_(executor) {}
