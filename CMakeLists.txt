cmake_minimum_required(VERSION 3.14)
project(vtune_duckdb_example)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif ()

include(FetchContent)

# Download Intel® Instrumentation and Tracing Technology (ITT) and Just-In-Time (JIT) API.

FetchContent_Declare(
        ittapi
        GIT_REPOSITORY https://github.com/intel/ittapi.git
        GIT_TAG v3.24.6
)
FetchContent_MakeAvailable(ittapi)

# Download DuckDB.

if (WIN32)
    set(DUCKDB_URL_PLATFORM "windows-amd64")
elseif (UNIX)
    if (APPLE)
        set(DUCKDB_URL_PLATFORM "osx-universal")
    else ()
        set(DUCKDB_URL_PLATFORM "linux-amd64")
    endif ()
else ()
    message(FATAL_ERROR "Unsupported platform.")
endif ()

FetchContent_Declare(
        duckdb
        URL https://github.com/duckdb/duckdb/releases/download/v0.8.1/libduckdb-${DUCKDB_URL_PLATFORM}.zip
)

FetchContent_GetProperties(duckdb)
if (NOT duckdb_POPULATED)
    FetchContent_Populate(duckdb)
endif ()

find_library(DUCKDB_LIBRARY NAMES duckdb PATHS ${duckdb_SOURCE_DIR} NO_CMAKE_SYSTEM_PATH)

if (NOT DUCKDB_LIBRARY)
    message(FATAL_ERROR "DuckDB was not found.")
endif ()

# Add and link the executable.

add_executable(vtune_duckdb_example main.cpp)
target_include_directories(vtune_duckdb_example PRIVATE ${duckdb_SOURCE_DIR})
target_link_libraries(vtune_duckdb_example PRIVATE ittnotify ${DUCKDB_LIBRARY})
