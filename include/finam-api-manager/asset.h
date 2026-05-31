#pragma once
#include <string>
#include <vector>

#include "auth.h"
#include "executor.h"

class AssetService {
   public:
    AssetService(AuthService& auth, Executor& executor);

    std::vector<Asset> Assets();
    std::vector<Asset> AllAssets(std::string cursor, bool only_active,
                                 bool only_disabled);  // тут будет пагинация
    Time Clock();
    void GetAsset();
    void GetConstituents();
    void GetAssetParams();
    Schedule GetSchedule(std::string symbol);
    void OptionsChain();
    std::vector<Exchange> Exchanges();

   private:
    AuthService& auth_;
    Executor& executor_;
};