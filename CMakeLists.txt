# Top level CMake project
cmake_minimum_required(VERSION 3.15)
project(QtPyPlugin LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# Enforce out-of-source build, fail otherwise
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

# Google Libraries
find_package(GTest CONFIG REQUIRED) # Gtest/mock
#-
#find_package(benchmark CONFIG REQUIRED) # Benchmark
#find_package(absl CONFIG REQUIRED) # Abseil
#find_package(gflags CONFIG REQUIRED) # Gflags
#find_package(glog CONFIG REQUIRED) # Glog


# Enforce Qt is located with its designated modules
find_package(Qt6 REQUIRED COMPONENTS Core Sql)

# Enable Qt specific compilers
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# This is required for Qt moc compiler:
# https://cmake.org/cmake/help/latest/policy/CMP0100.html
cmake_policy(SET CMP0100 NEW)

# Project source directory
set(PrjSrc ${CMAKE_SOURCE_DIR}/src)


enable_testing()
add_subdirectory(src)



