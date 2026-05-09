#pragma once
#include <string>
#include "auth.h"
#include "executor.h"

class AssetService {
public:
    AssetService(AuthService& auth, Executor& executor);

    void Assets();
    void AllAssets();
    std::string Clock();
    void GetAsset();
    void GetConstituents();
    void GetAssetParams();
    void Schedule();
    void OptionsChain();
    void Exchanges();
private:
    AuthService& auth_;
    Executor& executor_;
};