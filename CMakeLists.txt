cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPR_USE_SYSTEM_CURL ON)
set(BUILD_TZ_LIB ON CACHE BOOL "Build tz library")

option(ENABLE_TESTS "Enable tests" On)
option(ENABLE_EXAMPLES "Enable examples" Off)
option(ENABLE_INTERNAL "Enable internal" Off)

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

set(ADDRESS_SANITIZER_AVAILABLE OFF CACHE INTERNAL "" FORCE)
set(THREAD_SANITIZER_AVAILABLE OFF CACHE INTERNAL "" FORCE)
set(MEMORY_SANITIZER_AVAILABLE OFF CACHE INTERNAL "" FORCE)
set(UNDEFINED_SANITIZER_AVAILABLE OFF CACHE INTERNAL "" FORCE)

FetchContent_MakeAvailable(cpr json date)

add_library(finam-api-manager 
        src/client.cpp
        src/executor.cpp
        src/models.cpp
        src/account.cpp
        src/asset.cpp
        src/auth.cpp
        src/data.cpp
        src/metrics.cpp
        src/order.cpp
        src/report.cpp
)

target_include_directories(finam-api-manager PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(finam-api-manager PUBLIC cpr::cpr nlohmann_json::nlohmann_json date::date-tz)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(ENABLE_INTERNAL)
    add_subdirectory(internal)
endif()

if(ENABLE_EXAMPLES)
    add_subdirectory(examples)
endif()