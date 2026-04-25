cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CPR_USE_SYSTEM_CURL ON)
set(BUILD_TZ_LIB ON CACHE BOOL "Build tz library")

option(ENABLE_TESTS "Enable tests" ON)

project(finam-api-manager
        VERSION 1.0.0
        LANGUAGES CXX)

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

FetchContent_Declare(
        date
        GIT_REPOSITORY https://github.com/HowardHinnant/date.git
        GIT_TAG v3.0.4
)

FetchContent_MakeAvailable(cpr json date)

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
        src/service_time.cpp
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
        include/finam-api-manager/service_time.h
)
target_link_libraries(example PRIVATE finam-api-manager)

target_link_libraries(finam-api-manager PUBLIC cpr::cpr nlohmann_json::nlohmann_json date::date-tz)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()