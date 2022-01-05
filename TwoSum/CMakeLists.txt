cmake_minimum_required(VERSION 3.10)

# set the project name
project(TwoSum VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_BF "Brute Force solution" off)
option(USE_HM "Optimal (using hash map) solution" off)

message(STATUS "Solution: Brute Force - ${USE_BF}")
message(STATUS "Solution: Optimal with hash map - ${USE_HM}")

if(NOT USE_BF)
    if(NOT USE_HM)
        message(FATAL_ERROR "Choose solution: -DUSE_BF or -DUSE_HM")
    endif()
endif()

configure_file(TwoSumConfig.h.in TwoSumConfig.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(TwoSum TwoSum.cpp)
