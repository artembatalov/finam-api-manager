cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(finam-api-manager
        VERSION 1.0.0
        LANGUAGES CXX)

add_library(finam-api-manager src/client.cpp
        src/executor.cpp)

target_include_directories(finam-api-manager PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(example examples/main.cpp
        include/finam-trade-api/executor.h)
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
