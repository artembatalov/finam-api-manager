cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(finam-api-manager
        VERSION 1.0.0
        LANGUAGES CXX)

add_library(finam-api-manager src/client.cpp
        src/executor.cpp
        src/models.cpp
        src/service_account.cpp
        src/service_asset.cpp
        src/service_auth.cpp
        src/service_data.cpp
        src/service_metrics.cpp
        src/service_order.cpp
        src/service_report.cpp
)

target_include_directories(finam-api-manager PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(example examples/main.cpp
        include/finam-api-manager/executor.h
        include/finam-api-manager/models.h
        include/finam-api-manager/service_account.h
        include/finam-api-manager/service_order.h
        include/finam-api-manager/service_data.h
        include/finam-api-manager/service_asset.h
        include/finam-api-manager/service_metrics.h
        include/finam-api-manager/service_auth.h
        include/finam-api-manager/service_report.h
)
target_link_libraries(example PRIVATE finam-api-manager)

include(FetchContent)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.5
)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(cpr json)

target_link_libraries(finam-api-manager PUBLIC cpr::cpr nlohmann_json::nlohmann_json)
