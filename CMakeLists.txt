# Top level CMake project
cmake_minimum_required(VERSION 3.15)
project(QtBdbPlugin LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# Enforce out-of-source build, fail otherwise
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

# Google Libraries
set(GTest_DIR C:/opt/TC/local/lib/cmake/GTest)
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


# Common inc/lib/src locations by default
set(_opt /opt)
set(_opt_TC ${_opt}/TC)
set(_opt_TC_ext ${_opt_TC}/ext)

# Project source directory
set(PrjSrc ${CMAKE_SOURCE_DIR}/src)

# Identify compiler:
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using Gcc
  # lots of warnings and all warnings as errors
  #add_compile_options(-Wall -Wextra -pedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++

  # Berkeley DB
  set(bdb_prj ${_opt_TC_ext}/db-18.1.40)
  set(bdb_inc ${bdb_prj}/build_windows)
  set(bdb_stl_inc ${bdb_prj}/lang/cxx/stl)
  set(bdb_lib ${bdb_prj}/build_windows/x64/Debug)
  add_library(bdblib STATIC IMPORTED)
  set_target_properties(bdblib PROPERTIES IMPORTED_LOCATION ${bdb_lib}/libdb181d.lib)
  add_library(bdbstllib STATIC IMPORTED)
  set_target_properties(bdbstllib PROPERTIES IMPORTED_LOCATION ${bdb_lib}/libdb_stl181d.lib)

  # Needed for combining PDB files into single directory (WinDbg support)
  set(pdb_out ${CMAKE_CURRENT_BINARY_DIR}/pdb)
  set(CMAKE_PDB_OUTPUT_DIRECTORY ${pdb_out})
  set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${pdb_out})
  # end of MSVC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
 # using Clang/LLVM
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
 # using Intel C++
else()
  message(WARNING "Unknown compiler!") 
endif()


enable_testing()
add_subdirectory(src)



